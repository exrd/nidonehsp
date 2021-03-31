
#include <stdint.h>

#if defined(_WIN32)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT 
#endif

#if defined(_WIN32) && !defined(_WIN64)
#define EXPORT_CC __stdcall
#else
#define EXPORT_CC 
#endif

EXPORT int EXPORT_CC TestDynInt1(int arg0) { return arg0 * 2; }
EXPORT int EXPORT_CC TestDynInt2(int arg0, int arg1) { return arg0 * 2 + arg1 * 3; }
EXPORT int EXPORT_CC TestDynInt3(int arg0, int arg1, int arg2) { return arg0 * 2 + arg1 * 3 + arg2 * 4; }
EXPORT int EXPORT_CC TestDynInt4(int arg0, int arg1, int arg2, int arg3) { return arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5; }
EXPORT int EXPORT_CC TestDynInt8(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) { return arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5 + arg4 * 6 + arg5 * 7 + arg6 * 8 + arg7 * 9; }

EXPORT unsigned int EXPORT_CC TestDynUInt1(unsigned int arg0) { return arg0 * 2; }
EXPORT unsigned int EXPORT_CC TestDynUInt2(unsigned int arg0, unsigned int arg1) { return arg0 * 2 + arg1 * 3; }
EXPORT unsigned int EXPORT_CC TestDynUInt3(unsigned int arg0, unsigned int arg1, unsigned int arg2) { return arg0 * 2 + arg1 * 3 + arg2 * 4; }
EXPORT unsigned int EXPORT_CC TestDynUInt4(unsigned int arg0, unsigned int arg1, unsigned int arg2, unsigned int arg3) { return arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5; }
EXPORT unsigned int EXPORT_CC TestDynUInt8(unsigned int arg0, unsigned int arg1, unsigned int arg2, unsigned int arg3, unsigned int arg4, unsigned int arg5, unsigned int arg6, unsigned int arg7) { return arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5 + arg4 * 6 + arg5 * 7 + arg6 * 8 + arg7 * 9; }

EXPORT float EXPORT_CC TestDynFloat1(float arg0) { return arg0 * 2; }
EXPORT float EXPORT_CC TestDynFloat2(float arg0, float arg1) { return arg0 * 2 + arg1 * 3; }
EXPORT float EXPORT_CC TestDynFloat3(float arg0, float arg1, float arg2) { return arg0 * 2 + arg1 * 3 + arg2 * 4; }
EXPORT float EXPORT_CC TestDynFloat4(float arg0, float arg1, float arg2, float arg3) { return arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5; }

EXPORT void EXPORT_CC TestDynFloat1Ref(float* dst, float arg0) { *dst = arg0 * 2; }
EXPORT void EXPORT_CC TestDynFloat2Ref(float* dst, float arg0, float arg1) { *dst = arg0 * 2 + arg1 * 3; }
EXPORT void EXPORT_CC TestDynFloat3Ref(float* dst, float arg0, float arg1, float arg2) { *dst = arg0 * 2 + arg1 * 3 + arg2 * 4; }
EXPORT void EXPORT_CC TestDynFloat4Ref(float* dst, float arg0, float arg1, float arg2, float arg3) { *dst = arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5; }
EXPORT void EXPORT_CC TestDynFloat8Ref(float* dst, float arg0, float arg1, float arg2, float arg3, float arg4, float arg5, float arg6, float arg7) { *dst = arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5 + arg4 * 6 + arg5 * 7 + arg6 * 8 + arg7 * 9; }

EXPORT double EXPORT_CC TestDynDouble1(double arg0) { return arg0 * 2; }
EXPORT double EXPORT_CC TestDynDouble2(double arg0, double arg1) { return arg0 * 2 + arg1 * 3; }
EXPORT double EXPORT_CC TestDynDouble3(double arg0, double arg1, double arg2) { return arg0 * 2 + arg1 * 3 + arg2 * 4; }
EXPORT double EXPORT_CC TestDynDouble4(double arg0, double arg1, double arg2, double arg3) { return arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5; }

EXPORT void EXPORT_CC TestDynDouble1Ref(double* dst, double arg0) { *dst = arg0 * 2; }
EXPORT void EXPORT_CC TestDynDouble2Ref(double* dst, double arg0, double arg1) { *dst = arg0 * 2 + arg1 * 3; }
EXPORT void EXPORT_CC TestDynDouble3Ref(double* dst, double arg0, double arg1, double arg2) { *dst = arg0 * 2 + arg1 * 3 + arg2 * 4; }
EXPORT void EXPORT_CC TestDynDouble4Ref(double* dst, double arg0, double arg1, double arg2, double arg3) { *dst = arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5; }
EXPORT void EXPORT_CC TestDynDouble8Ref(double* dst, double arg0, double arg1, double arg2, double arg3, double arg4, double arg5, double arg6, double arg7) { *dst = arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5 + arg4 * 6 + arg5 * 7 + arg6 * 8 + arg7 * 9; }

EXPORT int32_t EXPORT_CC TestDynInt1Res32(int32_t arg0) { return arg0 * 2; }
EXPORT int32_t EXPORT_CC TestDynInt2Res32(int32_t arg0, int32_t arg1) { return arg0 * 2 + arg1 * 3; }
EXPORT int32_t EXPORT_CC TestDynInt3Res32(int32_t arg0, int32_t arg1, int32_t arg2) { return arg0 * 2 + arg1 * 3 + arg2 * 4; }
EXPORT int32_t EXPORT_CC TestDynInt4Res32(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3) { return arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5; }
EXPORT int32_t EXPORT_CC TestDynInt8Res32(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t arg6, int32_t arg7) { return arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5 + arg4 * 6 + arg5 * 7 + arg6 * 8 + arg7 * 9; }

EXPORT int64_t EXPORT_CC TestDynInt1Res64(int64_t arg0) { return arg0 * 2; }
EXPORT int64_t EXPORT_CC TestDynInt2Res64(int64_t arg0, int64_t arg1) { return arg0 * 2 + arg1 * 3; }
EXPORT int64_t EXPORT_CC TestDynInt3Res64(int64_t arg0, int64_t arg1, int64_t arg2) { return arg0 * 2 + arg1 * 3 + arg2 * 4; }
EXPORT int64_t EXPORT_CC TestDynInt4Res64(int64_t arg0, int64_t arg1, int64_t arg2, int64_t arg3) { return arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5; }
EXPORT int64_t EXPORT_CC TestDynInt8Res64(int64_t arg0, int64_t arg1, int64_t arg2, int64_t arg3, int64_t arg4, int64_t arg5, int64_t arg6, int64_t arg7) { return arg0 * 2 + arg1 * 3 + arg2 * 4 + arg3 * 5 + arg4 * 6 + arg5 * 7 + arg6 * 8 + arg7 * 9; }

EXPORT double EXPORT_CC TestDynVariant1(int arg0, float arg1, double arg2) { return (double)arg0 * 2 + (double)arg1 * 3 + (double)arg2 * 4; }
EXPORT int EXPORT_CC TestDynVariant2(double arg0, float arg1, int arg2) { return (int)((double)arg0 * 2 + (double)arg1 * 3 + (double)arg2 * 4); }
EXPORT int EXPORT_CC TestDynVariant3(int* dst, double arg0, float arg1, int arg2) { *dst = (int)((double)arg0 * 2 + (double)arg1 * 3 + (double)arg2 * 4); return *dst; }

typedef struct TestStruct TestStruct;
struct TestStruct
{
	int32_t i32_;
	double d_;
};
EXPORT int EXPORT_CC TestDynStruct1(TestStruct* dst, const TestStruct* src) { *dst = *src; return (int)(src->i32_ * 2 + src->d_ * 3); }
EXPORT TestStruct EXPORT_CC TestDynStruct2(const TestStruct* src) { return *src; }

