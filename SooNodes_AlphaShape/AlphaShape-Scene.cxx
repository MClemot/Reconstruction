#include <Misc.h>
#include "AlphaShape-Scene.h"

Scene::Scene()
{
	// ------ DATA INITIALIZATION
	UpdateRange();
	cout << "Cloud size " << vertices.size() << endl;
	selected_vertex = NULL;

	// ----- ROOT
	root = new SooGroupRender();

	// **********************************
	//
	//    AXES
	//
	// **********************************

	group_axes = new SooGroupColor(new SooAxes());
	group_axes->drawstyle->setStyle(SooDrawStyle::LINES);
	group_axes->drawstyle->setLineWidth(1.5);
	group_axes->color->set(0.0, 0.0, 1.0);
	group_axes->setDisplay(0);
	root->addChild(group_axes);

	// **********************************
	//
	//    VERTICES
	//
	// **********************************

	group_vertices = new SooGroupColor(new SooPointCloud(&vertices, &param_size_points_vertices));
	group_vertices->drawstyle->setStyle(SooDrawStyle::POINTS);
	group_vertices->color->set(0.0, 0.0, 0.0);
	group_vertices->setDisplay(1);
	root->addChild(group_vertices);

	// **********************************
	//
	//    CLICK
	//
	// **********************************

	group_selected_vertex = new SooGroupColor(new SooPointIdPtr(&selected_vertex));
	group_selected_vertex->drawstyle->setStyle(SooDrawStyle::POINTS);
	group_selected_vertex->drawstyle->setPointSize(6.0);
	group_selected_vertex->color->set(0.2, 0.2, 1.0);
	group_selected_vertex->setDisplay(1);
	root->addChild(group_selected_vertex);

	// **********************************
	//
	//    EMBELLISHED VERTICES
	//
	// **********************************

	group_vertices_embellished = new SooPointCloudEmbellished(&vertices, &param_size_spheres_vertices, &range);
	group_vertices_embellished->setDisplay(0);
	root->addChild(group_vertices_embellished);

	group_radius_spheres = new SooRadiusSpheres(&vertices, &poles_dist, &param_factor_spheres);
	group_radius_spheres->setDisplay(0);
	root->addChild(group_radius_spheres);

	// **********************************
	//
	//    EDGES
	//
	// **********************************

	s_edges = new SooEdges(&vertices, &edges);
	group_edges = new SooGroupColor(s_edges);
	group_edges->drawstyle->setStyle(SooDrawStyle::LINES);
	group_edges->drawstyle->setLineWidth(1.0);
	group_edges->color->set(0.0, 0.0, 0.2);
	group_edges->setDisplay(1);

	root->addChild(group_edges);

	s_voronoi = new SooVEdges(&voronoi);
	group_voronoi = new SooGroupColor(s_voronoi);
	group_voronoi->drawstyle->setStyle(SooDrawStyle::LINES);
	group_voronoi->drawstyle->setLineWidth(1.0);
	group_voronoi->color->set(0.5, 0.0, 0.0);
	group_voronoi->setDisplay(0);

	root->addChild(group_voronoi);

	group_debug = new SooGroupColor(new SooVEdges(&debug));
	group_debug->drawstyle->setStyle(SooDrawStyle::LINES);
	group_debug->drawstyle->setLineWidth(1.2);
	group_debug->color->set(0.0, 0.5, 0.0);
	group_debug->setDisplay(0);

	root->addChild(group_debug);

	// **********************************
	//
	//    TETRAHEDRA
	//
	// **********************************

	s_tetrahedra = new SooTrianglesVar(&vertices, &tetrahedra, &transparent, camera_position);
	group_tetrahedra = new SooGroupMaterial(s_tetrahedra);
	group_tetrahedra->material_filled->set(SooMaterial::COPPER);
	group_tetrahedra->material_filled->setTransparency(0.0);
	group_tetrahedra->material_lines->set(SooMaterial::OBSEDIAN);
	group_tetrahedra->set(SooGroupMaterial::FILLED);
	group_tetrahedra->setDisplay(1);

	root->addChild(group_tetrahedra);


	// **********************************
	//
	//    TRIANGLES
	//
	// **********************************

	s_triangles = new SooTrianglesVar(&vertices, &triangles, &transparent, camera_position);
	group_triangles = new SooGroupMaterial(s_triangles);
	group_triangles->material_filled->set(SooMaterial::GOLD);
	group_triangles->material_filled->setTransparency(0.2);
	group_triangles->material_lines->set(SooMaterial::OBSEDIAN);
	group_triangles->set(SooGroupMaterial::FILLED);
	group_triangles->setDisplay(1);

	root->addChild(group_triangles);

	root->printTree();
}

Scene::~Scene()
{
	delete root;
}

// *****************************************************
// 
//   U P D A T E   W I T H   C H A N G I N G   C A M E R A
//
// *****************************************************

void
Scene::UpdateWithCamera()
{
	if (transparent) {
		group_triangles->touch();
		group_tetrahedra->touch();
	}
}

// *****************************************************
// 
//   R E N D E R
//
// *****************************************************

void
Scene::render()
{
	root->render();
}

// *****************************************************
// 
//   P R O C E S S   A   C L I C K
//
// *****************************************************

int
Scene::process(SooNode* selection, double* click, int number, set<int>& set_elements)
{
	if ((selection == group_vertices->drawable) && ((selected_vertex == NULL) || (selected_vertex->index != number)))
	{
		if (selected_vertex != NULL)
			delete selected_vertex;
		selected_vertex = new PointId_3(vertices[number], number);
		UpdateSelectedVertex();
		return 1;
	}

	return 0;
}

// *****************************************************
//
//   U P D A T E   S C E N E
//
// *****************************************************

void
Scene::UpdateSelectedVertex()
{
	/*if (selected_vertex != NULL)
		cout << "Selected point has changed to " << selected_vertex->index << endl;
	else
		cout << "No selected point" << endl;*/

	if (selected_vertex != NULL)
		cout << "Selected point " << selected_vertex->index << " " << poles_dist[selected_vertex->index] << " " << poles_p_infinite[selected_vertex->index] << endl;
	group_selected_vertex->touch();
}

void
Scene::UpdateObject()
{
	UpdateRange();

	// No point is selected so far...
	if (selected_vertex != NULL)
		delete selected_vertex;
	UpdateSelectedVertex();

	group_edges->touch();
	group_debug->touch();
	group_voronoi->touch();
	group_vertices->touch();
	group_vertices_embellished->touch();
	group_triangles->touch();
	group_tetrahedra->touch();
}

void
Scene::UpdateRange()
{
	// Update the range
	if (vertices.empty())
		range.SetDefault();
	else
	{
		range.BoundingBox(vertices);
		if (vertices.size() == 1)
			cout << "do something" << endl;
	}
	//cout << range << endl;
}

void Scene::clearAll() {
	edges.clear();
	debug.clear();
	triangles.clear();
	tetrahedra.clear();
	t_numbersEdges.clear();
	t_numbersTriangles.clear();
	t_numbersTetrahedra.clear();
	alphasAll.clear();
	alphasEdges.clear();
	alphasTriangles.clear();
	alphasTetrahedra.clear();
	numberEdges = 0;
	numberTriangles = 0;
	numberTetrahedra = 0;
	voronoi.clear();
	poles_p.clear();
	poles_p_infinite.clear();
	poles_m.clear();
	poles_dist.clear();
}

void Scene::updateDraw() {
	group_edges->touch();
	group_triangles->touch();
	group_tetrahedra->touch();
	s_edges->n = edges.size();
	s_triangles->n = triangles.size();
	s_tetrahedra->n = 4 * tetrahedra.size();

	numberVertices = vertices.size();
	numberEdges = edges.size();
	numberTriangles = triangles.size();
	numberTetrahedra = tetrahedra.size();
	numberSimplices = numberVertices + numberEdges + numberTriangles + numberTetrahedra;
}


bool
Scene::LoadObject(const char* name)
{
	clearAll();
	simplex = Gudhi::Simplex_tree<>();

	std::vector<std::vector<int>> tmp_triangles;
	if (Load(vertices, tmp_triangles, name))
	{
		cout << "\ncomputing Voronoi diagram and poles" << endl;
		computeVoronoi();

		cout << "\ncomputing initial simpicial complex" << endl;

		if (method == 0) {
			if (!voronoi_weighted) {
				std::vector<GudhiPoint> pts;
				for (const Point_3& v : vertices)
					pts.push_back(GudhiPoint(v[0], v[1], v[2]));
				Gudhi::alpha_complex::Alpha_complex<GudhiKernel> alpha_complex(pts);
				alpha_complex.create_complex(simplex);
			}
			else {
				std::vector<GudhiWeightedPoint> pts;
				for (int i = 0; i < vertices.size(); ++i)
					pts.emplace_back(GudhiPoint(vertices[i][0], vertices[i][1], vertices[i][2]), poles_dist[i] / 4.);
				Gudhi::alpha_complex::Alpha_complex<GudhiKernel, true> alpha_complex(pts);
				alpha_complex.create_complex(simplex);
			}

			computeGeometricAlphaComplex();
		}
		else if (method == 1) {
			lfs_proximity_flag();
		}
		else {
			k_neighbors();
		}

		// Update the current name of the point cloud
		object_short_name = getShortName(name);
		UpdateObject();
		return true;
	}
	return false;
}

void Scene::randomPointsOnCircle(int n) {
	clearAll();
	vertices.clear();
	simplex = Gudhi::Simplex_tree<>();

	std::vector<double> angles(n);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 2.0*M_PI);
	std::normal_distribution<> noise_xy(0.0, 0.01);
	std::normal_distribution<> noise_z(0.0, 0.05);
	for (int i = 0; i < n; i++) {
		angles[i] = dis(gen);
		for (int j = 0; j < i; ++j) {
			if (abs(angles[i] - angles[j]) < M_PI / n) {
				i--;
				break;
			}

		}
	}
	sort(angles.begin(), angles.end());

	for (int i = 0; i < n; ++i)
		vertices.emplace_back(cos(angles[i]) + noise_xy(gen), sin(angles[i]) + noise_xy(gen), noise_z(gen));

	/*double sep = 100000.;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			sep = min(sep, CGAL::squared_distance(vertices[i], vertices[j]));
		}
	}
	
	std::normal_distribution<> noise(0.0, sep*sep/2.);
	for (int i = 0; i < n; ++i) {
		double x = noise_z(gen), y = noise_z(gen), z = noise_z(gen);
		while (CGAL::squared_distance(Point_3(0., 0., 0.), Point_3(x, y, z)) >= sep * sep * sep * sep / 16.) {
			x = noise_z(gen), y = noise_z(gen), z = noise_z(gen);
		}
		vertices[i] = Point_3(cos(angles[i]) + x, sin(angles[i]) + y, z);
	}*/

	for (int i = 0; i < vertices.size(); ++i)
		voronoi.push_back({ vertices[i], vertices[(i + 1) % vertices.size()] });

	cout << "\ncomputing initial simpicial complex" << endl;
	std::vector<GudhiPoint> pts;
	for (const Point_3& v : vertices)
		pts.push_back(GudhiPoint(v[0], v[1], v[2]));
	Gudhi::alpha_complex::Alpha_complex<GudhiKernel> alpha_complex(pts);
	alpha_complex.create_complex(simplex);
	computeGeometricAlphaComplex();

	int i = 0;
	for (const auto& tetra : simplex.complex_simplex_range()) {
		if (simplex.dimension(tetra) == 3)
			simplex.assign_key(tetra, i++);
	}
	for (const auto& tetra : simplex.complex_simplex_range()) {
		if (simplex.dimension(tetra) == 3) {
			cout << endl << simplex.key(tetra) << " ";
			for (const auto& tri : simplex.boundary_simplex_range(tetra)) {
				auto it = simplex.simplex_vertex_range(tri).begin();
				int a = *it, b = *(++it), c = *(++it);
				int d;
				for (const auto& v : simplex.simplex_vertex_range(tetra)) {
					if (v != a && v != b && v != c)
						d = v;
				}
				vector<int> v = { a,b,c };
				std::sort(v.begin(), v.end());
				Point_3 d1 (vertices[b].hx() - vertices[a].hx(), vertices[b].hy() - vertices[a].hy(), vertices[b].hz() - vertices[a].hz());
				Point_3 d2 (vertices[c].hx() - vertices[a].hx(), vertices[c].hy() - vertices[a].hy(), vertices[c].hz() - vertices[a].hz());
				Point_3 cross(d1.hy() * d2.hz() - d1.hz() * d2.hy(),
					          d1.hz() * d2.hx() - d1.hx() * d2.hz(),
					          d1.hx() * d2.hy() - d1.hy() * d2.hx());
				Point_3 dd (vertices[d].hx() - vertices[a].hx(), vertices[d].hy() - vertices[a].hy(), vertices[d].hz() - vertices[a].hz());
				if (dd.hx() * cross.hx() + dd.hy() * cross.hy() + dd.hz() * cross.hz() > 0)
					continue;
				for (const auto& tetra2 : simplex.cofaces_simplex_range(tri, 1)) {
					if (tetra != tetra2)
						cout << simplex.key(tetra2) << " ";
				}
			}
		}
	}

	UpdateObject();
}