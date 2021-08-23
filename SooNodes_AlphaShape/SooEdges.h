#ifndef __SOO_GEOM_H
#define __SOO_GEOM_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <FL/gl.h>
#include <FL/glu.h>

#include "SooDrawable.h"
#include "types-cgal.h"

class SooEdges : public SooDrawable
{
private:
	vector<Point_3>* vertices;
	vector<vector<int> >* edges;
public:
	int n;

	SooEdges(vector<Point_3>* vertices, vector<vector<int>>* edges) : SooDrawable("Edges"), vertices(vertices), edges(edges), n(0) {}

	void draw() {
		for (int i = 0; i < n; ++i) {
			glBegin(GL_LINES);
			glVertex3d((*vertices)[(*edges)[i][0]].x(), (*vertices)[(*edges)[i][0]].y(), (*vertices)[(*edges)[i][0]].z());
			glVertex3d((*vertices)[(*edges)[i][1]].x(), (*vertices)[(*edges)[i][1]].y(), (*vertices)[(*edges)[i][1]].z());
			glEnd();
		}
	}
};

class SooVEdges : public SooDrawable
{
private:
	vector<vector<Point_3> >* edges;
public:
	SooVEdges(vector<vector<Point_3> >* edges) : SooDrawable("Voronoi Edges"), edges(edges) {}

	void draw() {
		for (int i = 0; i < edges->size(); ++i) {
			glBegin(GL_LINES);
			glVertex3d((*edges)[i][0].x(), (*edges)[i][0].y(), (*edges)[i][0].z());
			glVertex3d((*edges)[i][1].x(), (*edges)[i][1].y(), (*edges)[i][1].z());
			glEnd();
		}
	}
};

#endif