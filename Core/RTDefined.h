#pragma once

#ifndef Delete_Pointer
#define Delete_Pointer(x) if(x) { delete x; x=nullptr;}
#endif // !DELETE

#ifndef Delete_Array_Pointer
#define Delete_Array_Pointer(x) if(x){delete[]x; x=nullptr;}
#endif // Delete_Array_Pointer

#ifndef Cast_UnChar
#define Cast_UnChar(x) static_cast<unsigned char>(x);
#endif 