#include "AlphaShape-Scene.h"

void Scene::computeVoronoi() {
	//copy of points
	std::vector<CGALPoint> cgalpts;
	for (const Point_3& v : vertices)
		cgalpts.push_back(CGALPoint(v[0], v[1], v[2]));
	Triangulation3 dt3(cgalpts.begin(), cgalpts.end());

	//iterator on facets to draw all the Voronoi edges
	for (auto f : dt3.finite_facets()) {
		Triangulation3::Object o = dt3.dual(f);
		if (const Triangulation3::Segment* s = CGAL::object_cast<Triangulation3::Segment>(&o)) {
			CGALPoint p1 = s->point(0);
			CGALPoint p2 = s->point(1);
			voronoi.push_back({ Point_3(CGAL::to_double(p1[0]), CGAL::to_double(p1[1]), CGAL::to_double(p1[2])),
								Point_3(CGAL::to_double(p2[0]), CGAL::to_double(p2[1]), CGAL::to_double(p2[2])) });
		}
		else if (const Triangulation3::Ray* r = CGAL::object_cast<Triangulation3::Ray>(&o)) {
			CGALPoint p1 = r->source();
			CGALPoint p2 = r->source() + 10.*r->direction().vector();
			voronoi.push_back({ Point_3(CGAL::to_double(p1[0]), CGAL::to_double(p1[1]), CGAL::to_double(p1[2])),
								Point_3(CGAL::to_double(p2[0]), CGAL::to_double(p2[1]), CGAL::to_double(p2[2])) });
		}
	}

	//iterator on vertices to compute their poles
	for (int i = 0; i < cgalpts.size(); ++i) {
		poles_p.push_back(CGALPoint(0., 0., 0.));
		poles_p_infinite.push_back(false);
		poles_m.push_back(CGALPoint(0., 0., 0.));
		Triangulation3::Vertex_handle v;
		dt3.is_vertex(cgalpts[i], v);   // assert true
		std::vector<Triangulation3::Facet> facets;
		dt3.finite_incident_facets(v, std::back_inserter(facets));
		double dp = 0., dm = 0.;

		//positive pole loop
		for (Triangulation3::Facet f : facets) {
			Triangulation3::Object o = dt3.dual(f);
			//finite edge
			if (!poles_p_infinite[i]) {
				if (const Triangulation3::Segment* s = CGAL::object_cast<Triangulation3::Segment>(&o)) {
					double d0 = CGAL::squared_distance(s->point(0), cgalpts[i]), d1 = CGAL::squared_distance(s->point(1), cgalpts[i]);
					if (d0 > dp) {
						dp = d0;
						poles_p[i] = s->point(0);
					}
					if (d1 > dp) {
						dp = d1;
						poles_p[i] = s->point(1);
					}
				}
			}
			//infinite edge (vertex on convex hull)
			if (const Triangulation3::Ray* r = CGAL::object_cast<Triangulation3::Ray>(&o)) {
				if (!poles_p_infinite[i]) {
					poles_p_infinite[i] = true;
					dp = INFINITY;
					poles_p[i] = CGALPoint(0., 0., 0.);
				}
				poles_p[i] += r->to_vector();
			}
		}

		if (!poles_p_infinite[i])
			debug.push_back({ vertices[i],Point_3(poles_p[i].hx(), poles_p[i].hy(),poles_p[i].hz())});

		//negative pole loop
		for (Triangulation3::Facet f : facets) {
			Triangulation3::Object o = dt3.dual(f);
			if (const Triangulation3::Segment* s = CGAL::object_cast<Triangulation3::Segment>(&o)) {
				CGAL::Vector_3<Kernel> v;
				if(!poles_p_infinite[i])
					v = CGAL::Vector_3<Kernel> (cgalpts[i], poles_p[i]);
				else
					v = CGAL::Vector_3<Kernel> (CGALPoint(0., 0., 0.), poles_p[i]);
				CGAL::Vector_3<Kernel> v0(cgalpts[i], s->point(0));
				CGAL::Vector_3<Kernel> v1(cgalpts[i], s->point(1));
				if (CGAL::to_double(v * v0) < 0) {
					double d0 = CGAL::squared_distance(s->point(0), cgalpts[i]);
					if (d0 > dm) { 
						dm = d0;
						poles_m[i] = s->point(0);
					}
				}
				if (CGAL::to_double(v * v1) < 0) {
					double d1 = CGAL::squared_distance(s->point(1), cgalpts[i]);
					if (d1 > dm) {
						dm = d1;
						poles_m[i] = s->point(1);
					}
				}
			}
		}

		debug.push_back({ vertices[i],Point_3(poles_m[i].hx(), poles_m[i].hy(),poles_m[i].hz()) });

		poles_dist.push_back(min(dp, dm));
	}
}