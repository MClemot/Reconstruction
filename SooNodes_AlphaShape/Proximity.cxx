#include "AlphaShape-Scene.h"

void Scene::k_neighbors() {
	Neighbor_search::Tree tree(vertices.begin(), vertices.end());

	std::vector<GudhiPoint> pts;
	for (const Point_3& v : vertices)
		pts.push_back(GudhiPoint(v[0], v[1], v[2]));
	Gudhi::alpha_complex::Alpha_complex<GudhiKernel> alpha_complex(pts);
	alpha_complex.create_complex(simplex);

	/* translation in skeleton-blocker */

	SBComplex sbcomplex;
	for (const auto& v : vertices)
		sbcomplex.add_vertex();

	for (int i = 0; i < vertices.size(); ++i) {
		Neighbor_search search(tree, vertices[i], param_k_neighbors);
		for (const auto& it : search) {
			int v = std::distance(vertices.begin(), std::find(vertices.begin(), vertices.end(), it.first));
			if (simplex.find({ i,v }) != simplex.null_simplex())
				sbcomplex.add_edge_without_blockers(SBVertex_handle(i), SBVertex_handle(v));
		}
	}

	for (const auto& t : sbcomplex.complex_simplex_range()) {
		int d = t.dimension();
		auto it = t.begin();
		if (d == 2) {
			int v1 = *it, v2 = *(++it), v3 = *(++it);
			if (simplex.find({ v1,v2,v3 }) == simplex.null_simplex())
				sbcomplex.add_blocker(SBSimplex(SBVertex_handle(v1),SBVertex_handle(v2),SBVertex_handle(v3)));
		}
		else if (d == 3) {
			int v1 = *it, v2 = *(++it), v3 = *(++it), v4 = *(++it);
			if (simplex.find({ v1,v2,v3,v4 }) == simplex.null_simplex())
				sbcomplex.add_blocker(SBSimplex(SBVertex_handle(v1),SBVertex_handle(v2),SBVertex_handle(v3),SBVertex_handle(v4)));
		}
	}

	/* collapsing according to the size of the link */

	if (mode2_collapse) {
		cout << "link statistics before collapsing" << endl;
		linkStatisticsSB(sbcomplex);

		cout << "collapsing" << endl;
		collapseSBEdges(sbcomplex);
		collapseSBVertices(sbcomplex);

		cout << "link statistics after collapsing" << endl;
		linkStatisticsSB(sbcomplex);
	}

	/* filling of SooNodes structures for drawing */

	for (const auto& t : sbcomplex.complex_simplex_range()) {
		int d = t.dimension();
		auto it = t.begin();
		if (d == 1) {
			int v1 = *it, v2 = *(++it);
			edges.push_back({ v1,v2 });
		}
		else if (d == 2) {
			int v1 = *it, v2 = *(++it), v3 = *(++it);
			triangles.push_back({ v1,v2,v3 });
		}
		else if (d == 3) {
			int v1 = *it, v2 = *(++it), v3 = *(++it), v4 = *(++it);
			tetrahedra.push_back({ v1,v2,v3 });
			tetrahedra.push_back({ v1,v2,v4 });
			tetrahedra.push_back({ v1,v3,v4 });
			tetrahedra.push_back({ v2,v3,v4 });
		}
	}

	updateDraw();
}


void Scene::lfs_proximity_flag() {
	std::vector<GudhiPoint> pts;
	for (const Point_3& v : vertices)
		pts.push_back(GudhiPoint(v[0], v[1], v[2]));
	Gudhi::alpha_complex::Alpha_complex<GudhiKernel> alpha_complex(pts);
	alpha_complex.create_complex(simplex);

	SBComplex sbcomplex;
	for (const auto& v : vertices)
		sbcomplex.add_vertex();
	for (const auto& e : simplex.skeleton_simplex_range(1)) {
		if (simplex.dimension(e)) {
			auto it = simplex.simplex_vertex_range(e).begin();
			int v1 = *it, v2 = *(++it);
			double d = sqrt(CGAL::squared_distance(vertices[v1], vertices[v2]));
			if (d <= sqrt(poles_dist[v1]) * param_threshold_lfs || d <= sqrt(poles_dist[v2]) * param_threshold_lfs) {
				edges.push_back({ v1, v2 });
				sbcomplex.add_edge_without_blockers(SBVertex_handle(v1), SBVertex_handle(v2));
			}
		}
	}
	for (const auto& t : sbcomplex.complex_simplex_range()) {
		int d = t.dimension();
		auto it = t.begin();
		if (d == 2) {
			int v1 = *it, v2 = *(++it), v3 = *(++it);
			if (simplex.find({ v1,v2,v3 }) != simplex.null_simplex())
				triangles.push_back({ v1,v2,v3 });
		}
		if (d == 3) {
			int v1 = *it, v2 = *(++it), v3 = *(++it), v4 = *(++it);
			if (simplex.find({ v1,v2,v3,v4 }) != simplex.null_simplex()) {
				tetrahedra.push_back({ v1,v2,v3 });
				tetrahedra.push_back({ v1,v2,v4 });
				tetrahedra.push_back({ v1,v3,v4 });
				tetrahedra.push_back({ v2,v3,v4 });
			}
		}
	}

	updateDraw();
}