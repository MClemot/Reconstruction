#include "AlphaShape-Scene.h"

inline vector<int> Scene::betti_numbers(Simplex_tree& st, int c) {
	Persistent_cohomology pcoh(st, true);
	pcoh.init_coefficients(2);
	pcoh.compute_persistent_cohomology();
	if (c==2)
		return { pcoh.betti_number(0), pcoh.betti_number(1) };
	else
		return { pcoh.betti_number(0), pcoh.betti_number(1), pcoh.betti_number(2) };
}

void Scene::linkStatistics() {
	std::map<std::vector<int>, int> m_e, m_v, m_t;
	Simplex_tree link;

	for (const auto& v : simplex.complex_vertex_range()) {
		linkVertex(v, link);
		m_v[betti_numbers(link, 3)] += 1;
	}
	for (const auto& s : simplex.skeleton_simplex_range(2)) {
		if (simplex.dimension(s) == 1) {
			linkEdge(s, link);
			m_e[betti_numbers(link, 3)] += 1;
		}
		if (simplex.dimension(s) == 2) {
			linkTriangle(s, link);
			m_t[betti_numbers(link, 3)] += 1;
		}
	}

	cout << "Betti numbers of vertices :" << endl;
	for (auto it = m_v.begin(); it != m_v.end(); ++it) {
		for (int b : it->first)
			cout << b << " ";
		cout << ": " << it->second << endl;
	}
	cout << "Betti numbers of edges :" << endl;
	for (auto it = m_e.begin(); it != m_e.end(); ++it) {
		for (int b : it->first)
			cout << b << " ";
		cout << ": " << it->second << endl;
	}
	cout << "Betti numbers of triangles :" << endl;
	for (auto it = m_t.begin(); it != m_t.end(); ++it) {
		for (int b : it->first)
			cout << b << " ";
		cout << ": " << it->second << endl;
	}
}

void Scene::linkVertex(Vertex_handle v, Simplex_tree& link) {
	link = Simplex_tree();
	Simplex_handle sv = simplex.find({ v });

	for (const auto& t : simplex.star_simplex_range(sv)) {
		vector<Vertex_handle> vert;
		for (const auto& vt : simplex.simplex_vertex_range(t)) {
			if (vt != v)
				vert.push_back(vt);
		}
		link.insert_simplex_and_subfaces(vert);
	}
}

void Scene::linkEdge(Simplex_handle e, Simplex_tree& link) {
	link = Simplex_tree();
	auto it = simplex.simplex_vertex_range(e).begin();
	int a = *it, b = *(++it);

	for (const auto& t : simplex.star_simplex_range(e)) {
		vector<Vertex_handle> vert;
		for (const auto& vt : simplex.simplex_vertex_range(t)) {
			if (vt != a && vt != b)
				vert.push_back(vt);
		}
		link.insert_simplex_and_subfaces(vert);
	}
}

void Scene::linkTriangle(Simplex_handle e, Simplex_tree& link) {
	link = Simplex_tree();
	auto it = simplex.simplex_vertex_range(e).begin();
	int a = *it, b = *(++it), c = *(++it);

	for (const auto& t : simplex.cofaces_simplex_range(e, 1)) {
		for (const auto& vt : simplex.simplex_vertex_range(t)) {
			if (vt != a && vt != b && vt != c) {
				link.insert_simplex({ vt });
				break;
			}	
		}
	}
}

void Scene::collapseTrianglesAndEdges() {
	bool again = true;
	while (again) {
		again = false;
		std::vector<std::pair<Simplex_handle, double>> _simplices;
		for (const auto& s : simplex.skeleton_simplex_range(2)) {
			if (simplex.dimension(s) == 1) {
				auto it = simplex.simplex_vertex_range(s).begin();
				Vertex_handle a = *it, b = *(++it);
				_simplices.push_back(std::make_pair(s, CGAL::squared_distance(vertices[a], vertices[b])));
			}
			else if (simplex.dimension(s) == 2)
				_simplices.push_back(std::make_pair(s, simplex.filtration(s)));
		}
		std::sort(_simplices.begin(), _simplices.end(), [](std::pair<Simplex_handle, double> a, std::pair<Simplex_handle, double> b) {
			return a.second > b.second;
			});
		for (const auto& s : _simplices) {
			Simplex_tree link;
			if (simplex.dimension(s.first) == 1) {
				linkEdge(s.first, link);
				vector<int> betti_n = betti_numbers(link, 2);
				if (betti_n[0] == 1 && betti_n[1] != 1) {
					auto it = simplex.simplex_vertex_range(s.first).begin();
					Vertex_handle a = *it, b = *(++it);
					for (const auto& t : simplex.cofaces_simplex_range(s.first, 2))
						simplex.remove_maximal_simplex(t);
					auto r = simplex.cofaces_simplex_range(simplex.find({ a,b }), 1);
					while (r.size() > 0) {
						simplex.remove_maximal_simplex(*r.begin());
						r = simplex.cofaces_simplex_range(simplex.find({ a,b }), 1);
					}
					simplex.remove_maximal_simplex(simplex.find({ a,b }));
					again = true;
					//break;
				}
			}
			else if (simplex.dimension(s.first) == 2) {
				linkTriangle(s.first, link);
				vector<int> betti_n = betti_numbers(link, 2);
				if (betti_n[0] == 1) {
					auto it = simplex.simplex_vertex_range(s.first).begin();
					Vertex_handle a = *it, b = *(++it), c = *(++it);
					simplex.remove_maximal_simplex(*simplex.cofaces_simplex_range(s.first, 1).begin());
					simplex.remove_maximal_simplex(simplex.find({ a,b,c }));
					again = true;
					//break;
				}
			}
		}
	}
}

void Scene::collapseTriangles() {
	bool again = true;
	while (again) {
		again = false;
		std::vector<std::pair<Simplex_handle, double>> _triangles;
		for (const auto& t : simplex.skeleton_simplex_range(2)) {
			if (simplex.dimension(t) == 2)
				_triangles.push_back(std::make_pair(t, simplex.filtration(t)));
		}
		std::sort(_triangles.begin(), _triangles.end(), [](std::pair<Simplex_handle, double> a, std::pair<Simplex_handle, double> b) {
			return a.second > b.second;
			});
		for (const auto& t : _triangles) {
			Simplex_tree link;
			linkTriangle(t.first, link);
			vector<int> betti_n = betti_numbers(link, 2);
			if (betti_n[0] == 1) {
				auto it = simplex.simplex_vertex_range(t.first).begin();
				Vertex_handle a = *it, b = *(++it), c = *(++it);
				simplex.remove_maximal_simplex(*simplex.cofaces_simplex_range(t.first, 1).begin());
				simplex.remove_maximal_simplex(simplex.find({ a,b,c }));
				again = true;
				//break;
			}
		}
	}
}

void Scene::collapseEdges() {
	bool again = true;
	while (again) {
		again = false;
		std::vector<std::pair<Simplex_handle, double>> _edges;
		for (const auto& e : simplex.skeleton_simplex_range(1)) {
			if (simplex.dimension(e) == 1) {
				auto it = simplex.simplex_vertex_range(e).begin();
				Vertex_handle a = *it, b = *(++it);
				_edges.push_back(std::make_pair(e, CGAL::squared_distance(vertices[a], vertices[b])));
			}
		}
		std::sort(_edges.begin(), _edges.end(), [](std::pair<Simplex_handle, double> a, std::pair<Simplex_handle, double> b) {
			return a.second > b.second;
			});
		for (const auto& e : _edges) {
			Simplex_tree link;
			linkEdge(e.first, link);
			vector<int> betti_n = betti_numbers(link, 2);
			if (betti_n[0] == 1 && betti_n[1] != 1) {
				auto it = simplex.simplex_vertex_range(e.first).begin();
				Vertex_handle a = *it, b = *(++it);
				for (const auto& t : simplex.cofaces_simplex_range(e.first, 2))
					simplex.remove_maximal_simplex(t);
				auto r = simplex.cofaces_simplex_range(simplex.find({ a,b }), 1);
				while (r.size() > 0) {
					simplex.remove_maximal_simplex(*r.begin());
					r = simplex.cofaces_simplex_range(simplex.find({ a,b }), 1);
				}
				simplex.remove_maximal_simplex(simplex.find({ a,b }));
				again = true;
				//break;
			}
		}
	}
}

void Scene::collapseVertices() {
	bool again = true;
	while (again) {
		again = false;
		for (const auto& v : simplex.complex_vertex_range()) {
			Simplex_tree link;
			linkVertex(v, link);
			vector<int> betti_n = betti_numbers(link, 3);
			if (betti_n[0] == 1 && betti_n[1] == 0) {
				for (const auto& e : simplex.cofaces_simplex_range(simplex.find({ v }), 1))
					simplex.remove_maximal_simplex(e);
				simplex.remove_maximal_simplex(simplex.find({ v }));
				again = true;
			}
		}
	}
}

void Scene::collapse() {
	clearAll();
	simplex.prune_above_filtration(alpha);

	cout << "\nlink statistics before collapsing" << endl;
	linkStatistics();

	collapseEdges();
	cout << "\nlink statistics after collapsing edges" << endl;
	linkStatistics();

	collapseVertices();
	cout << "\nlink statistics after collapsing vertices" << endl;
	linkStatistics();

	/* final Betti numbers */
	cout << "\nfinal complex Betti numbers : ";
	vector<int> betti_n = betti_numbers(simplex, 3);
	cout << betti_n[0] << " " << betti_n[1] << " " << betti_n[2] << endl;
	betti = to_string(betti_n[0]) + " " + to_string(betti_n[1]) + " " + to_string(betti_n[2]);

	/* filling of SooNodes structures for drawing */

	cout << "drawing" << endl;
	for (const auto& t :simplex.complex_simplex_range()) {
		int d = simplex.dimension(t);
		auto it = simplex.simplex_vertex_range(t).begin();
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

	cout << "done" << endl;
	updateDraw();
}