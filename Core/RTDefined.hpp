#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>

#ifndef Delete_Pointer
#define Delete_Pointer(x) if(x) { delete x; x=nullptr;}
#endif // !DELETE

#ifndef Delete_Array_Pointer
#define Delete_Array_Pointer(x) if(x){delete[]x; x=nullptr;}
#endif // Delete_Array_Pointer

#ifndef Cast_UnChar
#define Cast_UnChar(x) static_cast<unsigned char>(x)
#endif 

#ifndef Cast_Int
#define Cast_Int(x) static_cast<int>(x)
#endif // !Cast_Int
#ifndef ONE_GAMAMA
#define ONE_GAMAMA 0.4545454545454545f
#endif
static unsigned long long seed = 1;
#define MMM 0x100000000LL  
#define CCC 0xB16  
#define AAA 0x5DEECE66DLL  

static double drand48()
{
	seed = (AAA * seed + CCC) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return  ((double)x / (double)MMM);
}

static glm::vec3 Random_vec_in_sphere() {
	glm::vec3 p;
	do {
		p = 2.0f*glm::vec3(drand48(), drand48(), drand48()) - glm::vec3(1.0f);
	} while (glm::dot(p, p) >= 1.0);
	return p;
}
