/*
   Copyright 2020 Daniel S. Buckstein

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

/*
	GPRO-Graphics1-TestConsole-main.c/.cpp
	Main entry point source file for a Windows console application.

	Modified by: ____________
	Modified because: ____________
*/


#include <stdio.h>
#include <stdlib.h>

#include "gpro/gpro-math/gproVector.h"


void testVector()
{
	// test array vector initializers and functions
	float3 av, bv, cv, dv;
	vec3default(av);								// -> a = (0, 0, 0)
	vec3init(bv, 1.0f, 2.0f, 3.0f);					// -> b = (1, 2, 3)
	vec3copy(dv, vec3init(cv, 4.0f, 5.0f, 6.0f));	// -> d = c = (4, 5, 6)
	vec3copy(av, dv);								// a = d			-> a = (4, 5, 6)
	vec3add(dv, bv);								// d += b			-> d = (4 + 1, 5 + 2, 6 + 3) = (5, 7, 9)
	vec3sum(dv, bv, bv);							// d = b + b		-> d = (1 + 1, 2 + 2, 3 + 3) = (2, 4, 6)
	vec3add(vec3sum(dv, cv, bv), av);				// d = c + b + a	-> d = (4 + 1 + 4, 5 + 2 + 5, 6 + 3 + 6) = (9, 12, 15)

#ifdef __cplusplus
	// test all constructors and operators
	vec3 a, b(1.0f, 2.0f, 3.0f), c(cv), d(c);		// default; init; copy array; copy
	a = d;											// assign						-> a = (4, 5, 6)
	d += b;											// add assign					-> d = (5, 7, 9)
	d = b + b;										// sum, init, assign			-> d = (2, 4, 6)
	d = c + b + a;									// sum, init, sum, init, assign	-> d = (9, 12, 15)
#endif	// __cplusplus

	vec3 test;
	vec3init(test.e, 1.0f, 2.0f, 3.0f);
	printf("%f %f %f \n", test.e[0], test.e[1], test.e[2]);
	printf("%f %f %f \n", test.e[0], test.e[1], test.e[2]);
}

#ifdef __cplusplus
// C++ file io includes
#include <fstream>
#include <string>
#include <iostream>
#include <gpro/gpro-math/gproVector.h>
#else // !__cplusplus
// C file io includes
#include <stdio.h>
#endif // __cplusplus

color ray_color(const ray& r) 
{
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y + 1.0f);
	return (1.0f - t) * color(1.0, 1.0, 1.0) + t * color(0.5f, 0.7f, 1.0f);
}

using namespace std;

int main(int const argc, char const* const argv[])
{
	//testVector();

	// Image
	const float aspect_ratio = 16.0f / 9.0f;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// Camera

	float viewport_height = 2.0;
	float viewport_width = aspect_ratio * viewport_height;
	float focal_length = 1.0;

	point3 origin = point3(0, 0, 0);
	vec3 horizontal = vec3(viewport_width, 0, 0);
	vec3 vertical = vec3(0, viewport_height, 0);
	vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	printf("\n\n");
	//system("pause");

	ofstream file("image.ppm");

	file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		cerr << "\rScanlines remaining: " << j << ' ' << flush;
		for (int i = 0; i < image_width; ++i)
		{
			float u = float(i) / (image_width - 1);
			float v = float(j) / (image_height - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pixel_color = ray_color(r);
		}
	}

	cerr << "\nDone.\n";
	file.close();

	//system("build\Release\GPRO-Graphics1-TestConsole.exe > image.ppm");
}
