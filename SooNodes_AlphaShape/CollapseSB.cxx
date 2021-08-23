#include "AlphaShape-Scene.h"

inline vector<int> Scene::betti_numbers(const SBComplex& sbcomplex, int c) {
	Simplex_tree st;
	for (const auto& s : sbcomplex.complex_simplex_range())
		st.insert_simplex_and_subfaces(vector<Vertex_handle>(s.begin(), s.end()));
	return betti_numbers(st, c);
}

void Scene::linkStatisticsSB(const SBComplex& sbcomplex) {
	std::map<std::vector<int>, int> m_e, m_v, m_t;

	for (const auto& v : sbcomplex.vertex_range())
		m_v[betti_numbers(sbcomplex.link(v), 3)] += 1;

	for (const auto& e : sbcomplex.edge_range())
		m_e[betti_numbers(sbcomplex.link(e), 3)] += 1;

	for (const auto& t : sbcomplex.triangle_range())
		m_t[betti_numbers(sbcomplex.link(t), 3)] += 1;

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

void Scene::collapseSBTriangles(SBComplex& sbcomplex) {
	using MeasuredTriangle = std::pair<SBSimplex, double>;
	auto comp = [](MeasuredTriangle a, MeasuredTriangle b) { return a.second < b.second; };
	std::priority_queue<MeasuredTriangle, std::vector<MeasuredTriangle>, decltype(comp)> q(comp);
	std::map<SBSimplex, bool> m;
	for (const auto& t : sbcomplex.triangle_range()) {
		auto it = t.begin();
		Vertex_handle a = *it, b = *(++it), c = *(++it);
		q.emplace(t, simplex.filtration(simplex.find({ a,b,c })));
		m[t] = true;
	}
	while (!q.empty()) {
		MeasuredTriangle t = q.top();
		q.pop();
		m[t.first] = false;
		auto it = t.first.begin();
		SBVertex_handle a = *it, b = *(++it), c = *(++it);
		const auto link = sbcomplex.link(t.first);
		vector<int> betti_n = betti_numbers(link, 2);
		if (betti_n[0] == 1) {
			SBVertex_handle d = sbcomplex.convert_handle_from_another_complex(link, SBVertex_handle(0));
			if (!m[SBSimplex(a, b, d)]) {
				q.emplace(SBSimplex(a, b, d), simplex.filtration(simplex.find({ a,b,d })));
				m[SBSimplex(a, b, d)] = true;
			}
			if (!m[SBSimplex(a, c, d)]) {
				q.emplace(SBSimplex(a, c, d), simplex.filtration(simplex.find({ a,c,d })));
				m[SBSimplex(a, c, d)] = true;
			}
			if (!m[SBSimplex(b, c, d)]) {
				q.emplace(SBSimplex(b, c, d), simplex.filtration(simplex.find({ b,c,d })));
				m[SBSimplex(b, c, d)] = true;
			}
			sbcomplex.add_blocker(SBSimplex( a,b,c,d ));
			sbcomplex.add_blocker(t.first);
		}
	}
}

void Scene::collapseSBEdges(SBComplex& sbcomplex) {
	using MeasuredEdge = std::pair<SBEdge_handle, double>;
	auto comp = [](MeasuredEdge a, MeasuredEdge b) { return a.second < b.second; };
	std::priority_queue<MeasuredEdge, std::vector<MeasuredEdge>, decltype(comp)> q (comp);
	std::map<SBEdge_handle, bool> m;
	for (const auto& e : sbcomplex.edge_range()) {
		q.emplace(e, CGAL::squared_distance(vertices[e.m_source], vertices[e.m_target]) / 4.); //simplex.filtration(simplex.find({ (Vertex_handle)e.m_source, (Vertex_handle)e.m_target }))
		m[e] = true;
	}
	while (!q.empty()) {
		MeasuredEdge e = q.top();
		q.pop();
		m[e.first] = false;
		const auto link = sbcomplex.link(e.first);
		vector<int> betti_n = betti_numbers(link, 2);
		if (betti_n[0] == 1 && betti_n[1] != 1) {
			for (const auto& ne : sbcomplex.edge_range(SBVertex_handle(e.first.m_source))) {
				if (!m[ne]) {
					q.emplace(ne, CGAL::squared_distance(vertices[ne.m_source], vertices[ne.m_target]));
					m[ne] = true;
				}
			}
			for (const auto& ne : sbcomplex.edge_range(SBVertex_handle(e.first.m_target))) {
				if (!m[ne]) {
					q.emplace(ne, CGAL::squared_distance(vertices[ne.m_source], vertices[ne.m_target]));
					m[ne] = true;
				}
			}
			for (const auto& ne : link.edge_range()) { //problème ici, local/global
				if (!m[ne]) {
					q.emplace(ne, CGAL::squared_distance(vertices[ne.m_source], vertices[ne.m_target]));
					m[ne] = true;
				}
			}
			sbcomplex.remove_edge(e.first);
		}
	}
}

void Scene::collapseSBTrianglesAndEdges(SBComplex& sbcomplex) {
	using MeasuredSimplex = std::pair<SBSimplex, double>;
	auto comp = [](MeasuredSimplex a, MeasuredSimplex b) { return a.second < b.second; };
	std::priority_queue<MeasuredSimplex, std::vector<MeasuredSimplex>, decltype(comp)> q(comp);
	std::map<SBSimplex, bool> m;

	for (const auto& e : sbcomplex.edge_range()) {
		q.emplace(sbcomplex.get_vertices(e), CGAL::squared_distance(vertices[e.m_source], vertices[e.m_target]) / 4.); //simplex.filtration(simplex.find({ (Vertex_handle)e.m_source, (Vertex_handle)e.m_target }))
		m[sbcomplex.get_vertices(e)] = true;
	}
	for (const auto& t : sbcomplex.triangle_range()) {
		auto it = t.begin();
		Vertex_handle a = *it, b = *(++it), c = *(++it);
		q.emplace(t, simplex.filtration(simplex.find({ a,b,c })));
		m[t] = true;
	}

	while (!q.empty()) {
		MeasuredSimplex s = q.top();
		q.pop();
		m[s.first] = false;
		if (s.first.dimension() == 1) {
			auto it = s.first.begin();
			SBVertex_handle a = *it, b = *(++it);
			const auto link = sbcomplex.link(s.first);
			vector<int> betti_n = betti_numbers(link, 2);
			if (betti_n[0] == 1 && betti_n[1] != 1) {
				for (const auto& ne : sbcomplex.edge_range(a)) {
					const SBSimplex sne = sbcomplex.get_vertices(ne);
					if (!m[sne]) {
						q.emplace(sne, CGAL::squared_distance(vertices[ne.m_source], vertices[ne.m_target]));
						m[sne] = true;
					}
				}
				for (const auto& ne : sbcomplex.edge_range(b)) {
					const SBSimplex sne = sbcomplex.get_vertices(ne);
					if (!m[sne]) {
						q.emplace(sne, CGAL::squared_distance(vertices[ne.m_source], vertices[ne.m_target]));
						m[sne] = true;
					}
				}
				for (const auto& ne : link.edge_range()) { //problème ici, local/global
					const SBSimplex sne = sbcomplex.get_vertices(ne);
					if (!m[sne]) {
						q.emplace(sne, CGAL::squared_distance(vertices[ne.m_source], vertices[ne.m_target]));
						m[sne] = true;
					}
				}
				sbcomplex.remove_edge(a, b);
			}
		}
		if (s.first.dimension() == 2) {
			auto it = s.first.begin();
			SBVertex_handle a = *it, b = *(++it), c = *(++it);
			const auto link = sbcomplex.link(s.first);
			vector<int> betti_n = betti_numbers(link, 2);
			if (betti_n[0] == 1) {
				SBVertex_handle d = sbcomplex.convert_handle_from_another_complex(link, SBVertex_handle(0));
				if (!m[SBSimplex(a, b, d)]) {
					q.emplace(SBSimplex(a, b, d), simplex.filtration(simplex.find({ a,b,d })));
					m[SBSimplex(a, b, d)] = true;
				}
				if (!m[SBSimplex(a, c, d)]) {
					q.emplace(SBSimplex(a, c, d), simplex.filtration(simplex.find({ a,c,d })));
					m[SBSimplex(a, c, d)] = true;
				}
				if (!m[SBSimplex(b, c, d)]) {
					q.emplace(SBSimplex(b, c, d), simplex.filtration(simplex.find({ b,c,d })));
					m[SBSimplex(b, c, d)] = true;
				}
				sbcomplex.add_blocker(SBSimplex(a, b, c, d));
				sbcomplex.add_blocker(s.first);
			}
		}
	}
}

void Scene::collapseSBVertices(SBComplex& sbcomplex) {
	bool again = true;
	while (again) {
		again = false;
		for (const auto& v : sbcomplex.vertex_range()) {
			vector<int> betti_n = betti_numbers(sbcomplex.link(v), 3);
			if (betti_n[0] == 1 && betti_n[1] == 0) {
				sbcomplex.remove_vertex(v);
				again = true;
			}
		}
	}
}

void Scene::collapseSB() {
	clearAll();
	simplex.prune_above_filtration(alpha);

	/* translation in skeleton-blocker */

	cout << "building skeleton-blocker" << endl;
	SBComplex sbcomplex;
	for (const auto& v : vertices)
		sbcomplex.add_vertex();

	for (const auto& e : simplex.filtration_simplex_range()) {
		if (simplex.dimension(e) == 1) {
			auto it = simplex.simplex_vertex_range(e).begin();
			int v1 = *it, v2 = *(++it);
			sbcomplex.add_edge(SBVertex_handle(v1), SBVertex_handle(v2));
		}
	}

	for (const auto& f : simplex.filtration_simplex_range()) {
		auto it = simplex.simplex_vertex_range(f).begin();
		if (simplex.dimension(f) == 2) {
			int v1 = *it, v2 = *(++it), v3 = *(++it);
			sbcomplex.add_simplex(SBSimplex(SBVertex_handle(v1), SBVertex_handle(v2), SBVertex_handle(v3)));
		}
		else if (simplex.dimension(f) == 3) {
			int v1 = *it, v2 = *(++it), v3 = *(++it), v4 = *(++it);
			sbcomplex.add_simplex(SBSimplex(SBVertex_handle(v1), SBVertex_handle(v2), SBVertex_handle(v3), SBVertex_handle(v4)));
		}
	}

	/* collapsing according to the size of the link */

	if (betti_debug) {
		cout << "\nlink statistics before collapsing" << endl;
		linkStatisticsSB(sbcomplex);
	}

	/*cout << "\ncollapsing triangles" << endl;
	collapseSBTriangles(sbcomplex);
	cout << "\nlink statistics after collapsing triangles" << endl;
	linkStatisticsSB(sbcomplex);

	cout << "\ncollapsing edges" << endl;
	collapseSBEdges(sbcomplex);
	cout << "\nlink statistics after collapsing edges" << endl;
	linkStatisticsSB(sbcomplex);*/

	cout << "\ncollapsing triangles and edges" << endl;
	collapseSBTrianglesAndEdges(sbcomplex);
	if (betti_debug) {
		cout << "\nlink statistics after collapsing triangles and edges" << endl;
		linkStatisticsSB(sbcomplex);
	}

	cout << "\ncollapsing vertices" << endl;
	collapseSBVertices(sbcomplex);
	if (betti_debug) {
		cout << "\nlink statistics after collapsing vertices" << endl;
		linkStatisticsSB(sbcomplex);
	}

	/*for (const auto& e : sbcomplex.edge_range()) {
		if (betti_numbers(sbcomplex.link(e), 2) != vector<int>({ 2,0 }))
			voronoi.push_back({ vertices[e.m_source], vertices[e.m_target] });
	}*/

	/* final Betti numbers */
	if (betti_debug) {
		cout << "\nfinal complex Betti numbers : ";
		vector<int> betti_n = betti_numbers(sbcomplex, 3);
		cout << betti_n[0] << " " << betti_n[1] << " " << betti_n[2] << endl;
		betti = to_string(betti_n[0]) + " " + to_string(betti_n[1]) + " " + to_string(betti_n[2]);
	}

	/* filling of SooNodes structures for drawing */

	cout << "\ndrawing" << endl;
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

	cout << "\ndone" << endl;
	updateDraw();
}

void Scene::collapseToLowerConvexHull() {
	clearAll();
	for (int i = 0; i < vertices.size(); ++i)
		voronoi.push_back({ vertices[i], vertices[(i + 1) % vertices.size()] });

	/* translation in skeleton-blocker */

	cout << "building skeleton-blocker" << endl;
	SBComplex sbcomplex;
	for (const auto& v : vertices)
		sbcomplex.add_vertex();
	cout << "...edges" << endl;
	for (const auto& e : simplex.filtration_simplex_range()) {
		if (simplex.dimension(e) == 1) {
			auto it = simplex.simplex_vertex_range(e).begin();
			int v1 = *it, v2 = *(++it);
			sbcomplex.add_edge(SBVertex_handle(v1), SBVertex_handle(v2));
		}
	}
	cout << "...triangles" << endl;
	for (const auto& f : simplex.filtration_simplex_range()) {
		auto it = simplex.simplex_vertex_range(f).begin();
		if (simplex.dimension(f) == 2) {
			int v1 = *it, v2 = *(++it), v3 = *(++it);
			sbcomplex.add_simplex(SBSimplex(SBVertex_handle(v1), SBVertex_handle(v2), SBVertex_handle(v3)));
		}
		else if (simplex.dimension(f) == 3) {
			int v1 = *it, v2 = *(++it), v3 = *(++it), v4 = *(++it);
			sbcomplex.add_simplex(SBSimplex(SBVertex_handle(v1), SBVertex_handle(v2), SBVertex_handle(v3), SBVertex_handle(v4)));
		}
	}

	bool again = true;
	while (again) {
		again = false;
		for (const auto& tetra : sbcomplex.complex_simplex_range()) {
			if (tetra.dimension() == 3) {
				auto it = tetra.begin();
				SBVertex_handle a = *it, b = *(++it), c = *(++it), d = *(++it);
				vector<SBSimplex> tri({ SBSimplex(a,b,c), SBSimplex(a,b,d), SBSimplex(a,c,d), SBSimplex(b,c,d) });
				vector<SBVertex_handle> fourth({ d,c,b,a });
				vector<SBSimplex> res;
				for (int i = 0; i < 4; ++i) {
					auto itt = tri[i].begin();
					SBVertex_handle ta = *itt, tb = *(++itt), tc = *(++itt);
					Point_3 d1(vertices[tb].hx() - vertices[ta].hx(), vertices[tb].hy() - vertices[ta].hy(), vertices[tb].hz() - vertices[ta].hz());
					Point_3 d2(vertices[tc].hx() - vertices[ta].hx(), vertices[tc].hy() - vertices[ta].hy(), vertices[tc].hz() - vertices[ta].hz());
					Point_3 cross(d1.hy() * d2.hz() - d1.hz() * d2.hy(),
						          d1.hz() * d2.hx() - d1.hx() * d2.hz(),
						          d1.hx() * d2.hy() - d1.hy() * d2.hx());
					Point_3 dd(vertices[fourth[i]].hx() - vertices[ta].hx(), vertices[fourth[i]].hy() - vertices[ta].hy(), vertices[fourth[i]].hz() - vertices[ta].hz());
					if (dd.hx() * cross.hx() + dd.hy() * cross.hy() + dd.hz() * cross.hz() < 0)
						res.push_back(tri[i]);
				}
				if (sbcomplex.link(res[0]).num_vertices() == 1 && sbcomplex.link(res[1]).num_vertices() == 1) {
					res[0].intersection(res[1]);
					auto itt = res[0].begin();
					SBVertex_handle ta = *itt, tb = *(++itt);
					sbcomplex.remove_edge(ta, tb);
					again = true;
					break;
				}
			}
		}
	}

	/* final Betti numbers */
	cout << "\nfinal complex Betti numbers : ";
	vector<int> betti_n = betti_numbers(sbcomplex, 3);
	cout << betti_n[0] << " " << betti_n[1] << " " << betti_n[2] << endl;
	betti = to_string(betti_n[0]) + " " + to_string(betti_n[1]) + " " + to_string(betti_n[2]);

	/* filling of SooNodes structures for drawing */

	cout << "\ndrawing" << endl;
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

	cout << "\ndone" << endl;
	updateDraw();
}