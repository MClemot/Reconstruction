#include "AlphaShape-Scene.h"

void Scene::computeGeometricAlphaComplex() {
	N = simplex.num_simplices();

	for (auto f_simplex : simplex.filtration_simplex_range()) {
		int d = simplex.dimension(f_simplex);
		if (d == 1) {
			numberEdges++;
			auto it = simplex.simplex_vertex_range(f_simplex).begin();
			edges.push_back({ *it, *(++it) });
			alphasEdges.push_back(simplex.filtration(f_simplex));
		}
		else if (d == 2) {
			numberTriangles++;
			auto it = simplex.simplex_vertex_range(f_simplex).begin();
			triangles.push_back({ *it, *(++it), *(++it) });
			alphasTriangles.push_back(simplex.filtration(f_simplex));
		}
		else if (d == 3) {
			numberTetrahedra++;
			auto it = simplex.simplex_vertex_range(f_simplex).begin();
			int v1 = *it, v2 = *(++it), v3 = *(++it), v4 = *(++it);
			tetrahedra.push_back({ v1,v2,v3 });
			tetrahedra.push_back({ v1,v2,v4 });
			tetrahedra.push_back({ v1,v3,v4 });
			tetrahedra.push_back({ v2,v3,v4 });
			alphasTetrahedra.push_back(simplex.filtration(f_simplex));
		}
		t_numbersEdges.push_back(numberEdges);
		t_numbersTriangles.push_back(numberTriangles);
		t_numbersTetrahedra.push_back(numberTetrahedra);
		alphasAll.push_back(simplex.filtration(f_simplex));
	}

	auto f_simplex = simplex.filtration_simplex_range().begin();
	std::advance(f_simplex, N / 2);
	alphamax = simplex.filtration(*f_simplex);
	numberSimplices = N / 2;
	std::cout << N << " " << alphamax << std::endl;
	updateAlpha(alphamax);
}


void Scene::updateAlpha(double a, int n) {
	alpha = a;

	if (n == -1) {
		for (numberEdges = 0; alphasEdges[numberEdges] <= alpha; ++numberEdges) {}
		for (numberTriangles = 0; alphasTriangles[numberTriangles] <= alpha; ++numberTriangles) {}
		for (numberTetrahedra = 0; alphasTetrahedra[numberTetrahedra] <= alpha; ++numberTetrahedra) {}

		numberVertices = vertices.size();
		numberSimplices = numberVertices + numberEdges + numberTriangles + numberTetrahedra;

		s_edges->n = numberEdges;
		s_triangles->n = numberTriangles;
		s_tetrahedra->n = 4 * numberTetrahedra;
	}
	else {
		s_edges->n = t_numbersEdges[n];
		s_triangles->n = t_numbersTriangles[n];
		s_tetrahedra->n = 4 * t_numbersTetrahedra[n];

		numberSimplices = n;
		numberVertices = min(vertices.size(), n);
		numberEdges = t_numbersEdges[n];
		numberTriangles = t_numbersTriangles[n];
		numberTetrahedra = t_numbersTetrahedra[n];

		alpha = alphasAll[n];
	}

	if (display_betti) {
		Simplex_tree st = simplex;
		st.prune_above_filtration(alpha);
		vector<int> betti_n = betti_numbers(st, 3);
		betti = to_string(betti_n[0]) + " " + to_string(betti_n[1]) + " " + to_string(betti_n[2]);
	}
	else
		betti = "";

	group_edges->touch();
	group_vertices->touch();
	group_vertices_embellished->touch();
	group_triangles->touch();
	group_tetrahedra->touch();
}