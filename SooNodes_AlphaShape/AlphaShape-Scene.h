#ifndef __SCENE_H
#define __SCENE_H

#include <FL/Fl.H>
#include <FL/gl.h>
#include <FL/glu.h> 

#include <SooGroupRender.h>
#include <SooGroupColor.h>
#include <SooGroupMaterial.h>
#include <SooAxes.h>
#include <SooPoints.h>
#include <GLScene.h>
#include <Algorithms.h>

#include <SooEdges.h>
#include <SooTrianglesVar.h>
#include <SooRadiusSpheres.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Orthogonal_k_neighbor_search.h>
#include <CGAL/Search_traits_3.h>

#include <gudhi/Simplex_tree.h>
#include <gudhi/Points_off_io.h>
#include <gudhi/Alpha_complex.h>
#include <gudhi/Skeleton_blocker.h>
#include <gudhi/Persistent_cohomology.h>

using GudhiKernel = CGAL::Epeck_d< CGAL::Dimension_tag<3> >;
using GudhiPoint = GudhiKernel::Point_d;
using GudhiWeightedPoint = GudhiKernel::Weighted_point_d;

using Simplex_tree = Gudhi::Simplex_tree<>;
using Simplex_handle = Gudhi::Simplex_tree<>::Simplex_handle;
using Vertex_handle = Gudhi::Simplex_tree<>::Vertex_handle;

using SBComplex = Gudhi::skeleton_blocker::Skeleton_blocker_complex<Gudhi::skeleton_blocker::Skeleton_blocker_simple_traits>;
using SBSimplex = SBComplex::Simplex;
using SBVertex_handle = SBComplex::Vertex_handle;
using SBEdge_handle = SBComplex::Edge_handle;

using Persistent_cohomology = Gudhi::persistent_cohomology::Persistent_cohomology<Simplex_tree, Gudhi::persistent_cohomology::Field_Zp>;

using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Triangulation3 = CGAL::Delaunay_triangulation_3<Kernel>;
using CGALPoint = Triangulation3::Point;

using TreeTraits = CGAL::Search_traits_3<K>;
using Neighbor_search = CGAL::Orthogonal_k_neighbor_search<TreeTraits>;

class UserInterface;

// Classe permettant de gerer une scene 3D.
// La scene comporte une camera, une lumiere
// et un ensemble d'objets dont on sait
// comment les afficher a l'aide d'une liste OpenGL

class Scene : public GLScene
{
public:
	// ****************************************************
	//
	//    DONNEES DE LA SCENE
	//
	// ****************************************************
	vector<Point_3> vertices; // Vector of vertices
	vector<vector<int>> edges; // Vector of edges
	vector<vector<Point_3>> debug;
	vector<vector<Point_3>> voronoi; // Vector of voronoi edges
	vector<vector<int>> triangles; // Vector of triangles
	vector<vector<int>> tetrahedra; // Vector of tetrahedra
	string object_short_name; // Short name for the object
	PointId_3* selected_vertex;

	vector<CGALPoint> poles_p;
	vector<bool> poles_p_infinite;
	vector<CGALPoint> poles_m;
	vector<double> poles_dist;

	// ================================================
	// Various parameters
	// ================================================
	double param_size_points_vertices = 2;
	double param_size_spheres_vertices = 0.01;
	double param_factor_spheres = 1.;
	double param_threshold_lfs = 1.;
	int param_k_neighbors = 10;
	bool transparent = true;

	bool voronoi_weighted = false;
	int method = 0;
	bool mode0_collapse = false;
	bool mode1_collapse = false;
	bool mode2_collapse = false;
	bool display_betti = true;
	bool betti_debug = true;

	// ****************************************************
	//
	//    SOO NODES
	//
	// ****************************************************

	// ----- Root
	SooGroupRender* root;

	// ----- Axis
	SooGroupColor* group_axes;

	// ----- Object
	SooGroupColor* group_vertices;

	SooEdges* s_edges;
	SooGroupColor* group_edges;
	SooVEdges* s_voronoi;
	SooGroupColor* group_voronoi;
	SooGroupColor* group_debug;

	SooPointCloudEmbellished* group_vertices_embellished;
	SooRadiusSpheres* group_radius_spheres;

	SooTrianglesVar* s_triangles;
	SooGroupMaterial* group_triangles;

	SooTrianglesVar* s_tetrahedra;
	SooGroupMaterial* group_tetrahedra;

	// ----- Info associated to a click
	SooGroupColor* group_selected_vertex;

	UserInterface* ui;

	double alphamax;
	double alpha;
	int N;
	int numberSimplices;
	int numberVertices;
	int numberEdges;
	int numberTriangles;
	int numberTetrahedra;
	std::vector<int> t_numbersEdges;
	std::vector<int> t_numbersTriangles;
	std::vector<int> t_numbersTetrahedra;
	std::vector<double> alphasAll;
	std::vector<double> alphasEdges;
	std::vector<double> alphasTriangles;
	std::vector<double> alphasTetrahedra;
	Gudhi::Simplex_tree<> simplex;

	string betti;

	/** Scene constructor */
	Scene();

	/** Scene destructor */
	~Scene();

	void render();
	int process(SooNode* selection, double* click, int element, set<int>& set_elements);
	void UpdateWithCamera();

	void UpdateSelectedVertex();
	void UpdateRange();
	void UpdateObject();
	bool LoadObject(const char*);

	void clearAll();
	void computeVoronoi();
	void computeGeometricAlphaComplex();
	void updateAlpha(double a, int n = -1);
	void updateDraw();

	void collapse();
	void collapseTrianglesAndEdges();
	void collapseTriangles();
	void collapseEdges();
	void collapseVertices();
	void collapseSB();
	void collapseSBTrianglesAndEdges(SBComplex& sbcomplex);
	void collapseSBTriangles(SBComplex& sbcomplex);
	void collapseSBEdges(SBComplex& sbcomplex);
	void collapseSBVertices(SBComplex& sbcomplex);
	void linkVertex(Vertex_handle v, Simplex_tree &link);
	void linkEdge(Simplex_handle e, Simplex_tree &link);
	void linkTriangle(Simplex_handle e, Simplex_tree& link);
	void linkStatistics();
	void linkStatisticsSB(const SBComplex& sbcomplex);
	vector<int> betti_numbers(Simplex_tree& st, int c);
	vector<int> betti_numbers(const SBComplex& sbcomplex, int c);

	void k_neighbors();
	void lfs_proximity_flag();

	void randomPointsOnCircle(int n);
	void collapseToLowerConvexHull();
};


#endif
