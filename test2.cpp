#include <iostream>
#include <graphics.h>


// constants
const int INSIDE = 0;  // 0000
const int LEFT = 1;    // 0001
const int RIGHT = 2;   // 0010
const int BOTTOM = 4;  // 0100
const int TOP = 8;     // 1000
int xLeft = 100, xRight = 300, yBottom = 200, yTop = 400;
//

// custom data types
struct Point {
	int x, y;
};
struct Line {
	Point start, end;
};
struct Building {
	Line left, right, top;
};
//

// functions declarations
int calculateRegionCode(Point p);
void cohenSutherland(Point &p1, Point &p2);
void flood(int x, int y, int new_col, int old_col);
//

int main() {
	
	int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    
    const int Y = getmaxy();
    const int X = getmaxx();
    
    // sky
    setbkcolor(BLUE);
    cleardevice();
    
    // sun
    circle(100,100,20);
    flood(100,100,YELLOW,BLUE);
    
    // road
    line(0, Y-40, X, Y-40);
    flood(1,Y-1,BLACK,BLUE);
    for(int i=0; i<getmaxx(); i+=10) if(i%20==0) line(i,Y-20, i+10, Y-20);
    
    // buildings array
    Building b[] =
	{
		// building 1
		{
	    	// left
			{
				{0,Y-40}, // start
				{0,Y-200} // end
			},
			// right
			{
				{100,Y-40}, // start
				{100,Y-200} // end
			},
			// top
			{
				{0,Y-200},  // start
				{100,Y-200} // end
			},
		},
		// building 2
		{
	    	// left
			{
				{100,Y-40}, // start
				{100,Y-250} // end
			},
			// right
			{
				{200,Y-40}, // start
				{200,Y-250} // end
			},
			// top
			{
				{100,Y-250},  // start
				{200,Y-250} // end
			},
		},
		// building 3
		{
	    	// left
			{
				{200,Y-40}, // start
				{200,Y-220} // end
			},
			// right
			{
				{300,Y-40}, // start
				{300,Y-220} // end
			},
			// top
			{
				{200,Y-220},  // start
				{300,Y-220} // end
			},
		},
		// building 4
		{
	    	// left
			{
				{300,Y-40}, // start
				{300,Y-300} // end
			},
			// right
			{
				{400,Y-40}, // start
				{400,Y-300} // end
			},
			// top
			{
				{300,Y-300},  // start
				{400,Y-300} // end
			},
		},
		// building 5
		{
	    	// left
			{
				{400,Y-40}, // start
				{400,Y-290} // end
			},
			// right
			{
				{500,Y-40}, // start
				{500,Y-290} // end
			},
			// top
			{
				{400,Y-290},  // start
				{500,Y-290} // end
			},
		},
		// building 6
		{
	    	// left
			{
				{500,Y-40}, // start
				{500,Y-200} // end
			},
			// right
			{
				{600,Y-40}, // start
				{600,Y-200} // end
			},
			// top
			{
				{500,Y-200},  // start
				{600,Y-200} // end
			},
		},		
	};
	int b_lenght = sizeof(b) / sizeof(b[0]);
	
	// CLIPPING CODE -- START
		// clipping buildings
		for (int i=0; i<b_lenght; i++) {
			// left
			cohenSutherland(b[i].left.start, b[i].left.end);
			// right
			cohenSutherland(b[i].right.start, b[i].right.end);
			// top
			cohenSutherland(b[i].top.start, b[i].top.end);
		}
		// draw clipping window 
		setcolor(GREEN);   
	    rectangle(xLeft, yBottom, xRight, yTop);
	    setcolor(WHITE);
    // CLIPPING CODE -- END
	
	// drawing buildings
	for (int i=0; i<b_lenght; i++) {
		
		// left
		line(b[i].left.start.x,b[i].left.start.y,b[i].left.end.x,b[i].left.end.y);
		// right		
		line(b[i].right.start.x,b[i].right.start.y,b[i].right.end.x,b[i].right.end.y);
		// top		
		line(b[i].top.start.x,b[i].top.start.y,b[i].top.end.x,b[i].top.end.y);
		
	}
	
    getch();
    closegraph();
    return 0;
}

// function definitions

void flood(int x, int y, int new_col, int old_col){
    if (getpixel(x, y) == old_col) {
        putpixel(x, y, new_col);
        flood(x + 1, y, new_col, old_col);
        flood(x - 1, y, new_col, old_col);
        flood(x, y + 1, new_col, old_col);
        flood(x, y - 1, new_col, old_col);
    }
}

int calculateRegionCode(Point p) {
	
    int code = INSIDE;
    if (p.x < xLeft)
        code |= LEFT;
    else if (p.x > xRight)
        code |= RIGHT;
    if (p.y < yBottom)
        code |= BOTTOM;
    else if (p.y > yTop)
        code |= TOP;
    return code;
}

void cohenSutherland(Point &p1, Point &p2) {
	
    int code1 = calculateRegionCode(p1);
    int code2 = calculateRegionCode(p2);
    bool accept = false;

    while (true) {
        if (!(code1 | code2)) {
            // both endpoints are inside the window
            accept = true;
            break;
        } else if (code1 & code2) {
            // both endpoints are outside the same region
            p1.x = 0; p2.x = 0; p1.y = 0; p2.y = 0;
            break;
        } else {
            // Clipping
            int codeOut = code1 ? code1 : code2;
            Point newPoint;

            if (codeOut & TOP) {
                newPoint.x = p1.x + (p2.x - p1.x) * (yTop - p1.y) / (p2.y - p1.y);
                newPoint.y = yTop;
            } else if (codeOut & BOTTOM) {
                newPoint.x = p1.x + (p2.x - p1.x) * (yBottom - p1.y) / (p2.y - p1.y);
                newPoint.y = yBottom;
            } else if (codeOut & RIGHT) {
                newPoint.y = p1.y + (p2.y - p1.y) * (xRight - p1.x) / (p2.x - p1.x);
                newPoint.x = xRight;
            } else if (codeOut & LEFT) {
                newPoint.y = p1.y + (p2.y - p1.y) * (xLeft - p1.x) / (p2.x - p1.x);
                newPoint.x = xLeft;
            }

            if (codeOut == code1) {
                p1 = newPoint;
                code1 = calculateRegionCode(p1);
            } else {
                p2 = newPoint;
                code2 = calculateRegionCode(p2);
            }
        }
    }
}