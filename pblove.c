#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include <time.h>


float f(float x, float y, float z) {
	float a = x * x + 9.0f / 4.0f * y * y + z * z - 1;
	return a * a * a - x * x * z * z * z - 9.0f / 80.0f * y * y * z * z * z;
}

float h(float x, float z) {
	for (float y = 1.0f; y >= 0.0f; y -= 0.001f)
		if (f(x, y, z) <= 0.0f)
			return y;
	return 0.0f;
}

int pblove() {
	HANDLE o = GetStdHandle(STD_OUTPUT_HANDLE);
	_TCHAR buffer[25][80] = { _T(' ') };
	_TCHAR ramp[] = _T(".:-=+*#%@");
	
	
	int cnt=0;
	time_t ss,ee;
	ss = time(NULL);
	for (float t = 0.0f;; t += 0.1f) {
		if(cnt==0)
			system("color 0");
		if(cnt==30)
			system("color 1");
		if(cnt==60)
			system("color c");
		if(cnt==90)
			system("color 3");
		if(cnt==120)
			system("color 4");
		if(cnt==150)
			system("color 5");
		if(cnt==180)
			system("color 6");
		if(cnt==210)
			system("color 7");
		if(cnt==240)
			system("color 8");
		if(cnt==270)
			system("color 9");
		if(cnt==300)
			system("color c");
		if(cnt==330)
			system("color 4");
		if(cnt==360)
			system("color c");
		if(cnt==390)
			system("color d");
		if(cnt==420)
			system("color e");
		if(cnt==450)
			system("color f");
		cnt++;
		if(cnt==480)
			cnt=0;
		int sy = 0;
		float s = sinf(t);
		float a = s * s * s * s * 0.2f;
		for (float z = 1.3f; z > -1.2f; z -= 0.1f) {
			_TCHAR* p = &buffer[sy++][0];
			float tz = z * (1.2f - a);
			for (float x = -1.5f; x < 1.5f; x += 0.05f) {
				float tx = x * (1.2f + a);
				float v = f(tx, 0.0f, tz);
				if (v <= 0.0f) {
					float y0 = h(tx, tz);
					float ny = 0.01f;
					float nx = h(tx + ny, tz) - y0;
					float nz = h(tx, tz + ny) - y0;
					float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
					float d = (nx + ny - nz) * nd * 0.5f + 0.5f;
					*p++ = ramp[(int)(d * 5.0f)];
				}
				else
					*p++ = ' ';
			}
			
		}
		
		for (sy = 0; sy < 25; sy++) {
			COORD coord = { 0, sy };
			SetConsoleCursorPosition(o, coord);
			WriteConsole(o, buffer[sy], 79, NULL, 0);
		}
		
		Sleep(2);
		ee = time(NULL);
		if(difftime(ee,ss) == 3) {
			return 0;
		}
		
	
	}
}

