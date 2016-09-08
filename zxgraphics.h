#ifndef _ZXGRAPHICS_H_
#define _ZXGRAPHICS_H_

extern void ZXplot(int x, int y, unsigned char colour);

extern void ZXunplot(int x, int y, unsigned char colour);

extern void ZXLine(int x1, int y1, int x2, int y2, unsigned char colour, unsigned char plotUnplot);

extern void ZXCircle(unsigned int xc, unsigned int yc, unsigned int r, unsigned char colour, unsigned char plotUnplot);

extern void ZXTriangle (int topx, int topy, int rightx, int righty, unsigned char colour, unsigned char plotUnplot);

extern void ZXSquare(int x, int y, int size, unsigned char colour, unsigned char plotUnplot);

extern void ZXRectangle(int x, int y, int width, int height, unsigned char colour, unsigned char plotUnplot);

extern void ZXEllipse(int cx, int cy, int XRadius, int YRadius, unsigned char colour, unsigned char plotUnplot);

extern void ZXArc(int cx, int cy, int xRadius, int yRadius, unsigned char colour, unsigned char plotUnplot);

extern void ZXParabola(int xc, int yc, int p, int bound, unsigned char colour, unsigned char plotUnplot);

extern void FilledCircle(int x, int y, int r, unsigned char colour, unsigned char plotUnplot);

extern void bezier(int x1, int y1, int x2, int y2, int x3, int y3, unsigned char colour, unsigned char plotUnplot);

extern void bezier2(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, unsigned char colour, unsigned char plotUnplot);

extern void ZXQuad1(int x1, int y1, int ctrlX, int ctrlY, int x2, int y2, unsigned char steps, unsigned char colour, unsigned char plotUnplot);

extern void ZXQuadraticBezier(int x1, int y1, int ctrlX, int ctrlY, int x2, int y2, unsigned char steps, unsigned char colour, unsigned char plotUnplot);

extern void ZXQuadraticBezier1(int x1, int y1, int ctrlX, int ctrlY, int x2, int y2, unsigned char steps, unsigned char colour, unsigned char plotUnplot);

extern void ZXCubicBezier(int x1, int y1, int ctrlx1, int ctrly1, int ctrlx2, int ctrly2, int x2, int y2, unsigned char steps, unsigned char colour, unsigned char plotUnplot);

extern void bezier4(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, unsigned char colour, unsigned char plotUnplot);

extern void DrawBezierFX( int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy, unsigned char colour, unsigned char plotUnplot);

//extern void parabola(int xc, int yc, int p, int bound, unsigned char colour, unsigned char plotUnplot);


#endif