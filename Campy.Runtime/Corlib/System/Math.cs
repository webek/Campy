// Copyright (c) 2012 DotNetAnywhere
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

using System.Runtime.CompilerServices;

#if LOCALTEST
using System;
namespace System_ {
#else
namespace System {
#endif
    public static class Math {

        public const double E = 2.7182818284590452354;
        public const double PI = 3.14159265358979323846;

        #region Abs()

        public static sbyte Abs(sbyte v) {
            if (v == sbyte.MinValue) {
                throw new OverflowException("Value is too small");
            }
            return (v >= 0) ? v : (sbyte)-v;
        }

        public static short Abs(short v) {
            if (v == short.MinValue) {
                throw new OverflowException("Value is too small");
            }
            return (v >= 0) ? v : (short)-v;
        }

        public static int Abs(int v) {
            if (v == int.MinValue) {
                throw new OverflowException("Value is too small");
            }
            return (v >= 0) ? v : -v;
        }

        public static long Abs(long v) {
            if (v == long.MinValue) {
                throw new OverflowException("Value is too small");
            }
            return (v >= 0) ? v : -v;
        }

        public static float Abs(float v) {
            return (v >= 0) ? v : -v;
        }

        public static double Abs(double v) {
            return (v >= 0) ? v : -v;
        }

        #endregion

        #region Min()

        public static sbyte Min(sbyte v1, sbyte v2) {
            return (v1 < v2) ? v1 : v2;
        }

        public static short Min(short v1, short v2) {
            return (v1 < v2) ? v1 : v2;
        }

        public static int Min(int v1, int v2) {
            return (v1 < v2) ? v1 : v2;
        }

        public static long Min(long v1, long v2) {
            return (v1 < v2) ? v1 : v2;
        }

        public static byte Min(byte v1, byte v2) {
            return (v1 < v2) ? v1 : v2;
        }

        public static ushort Min(ushort v1, ushort v2) {
            return (v1 < v2) ? v1 : v2;
        }

        public static uint Min(uint v1, uint v2) {
            return (v1 < v2) ? v1 : v2;
        }

        public static ulong Min(ulong v1, ulong v2) {
            return (v1 < v2) ? v1 : v2;
        }

        public static float Min(float v1, float v2) {
            if (float.IsNaN(v1) || float.IsNaN(v2)) {
                return float.NaN;
            }
            return (v1 < v2) ? v1 : v2;
        }

        public static double Min(double v1, double v2) {
            if (double.IsNaN(v1) || double.IsNaN(v2)) {
                return double.NaN;
            }
            return (v1 < v2) ? v1 : v2;
        }

        #endregion

        #region Max()

        public static sbyte Max(sbyte v1, sbyte v2) {
            return (v1 > v2) ? v1 : v2;
        }

        public static short Max(short v1, short v2) {
            return (v1 > v2) ? v1 : v2;
        }

        public static int Max(int v1, int v2) {
            return (v1 > v2) ? v1 : v2;
        }

        public static long Max(long v1, long v2) {
            return (v1 > v2) ? v1 : v2;
        }

        public static byte Max(byte v1, byte v2) {
            return (v1 > v2) ? v1 : v2;
        }

        public static ushort Max(ushort v1, ushort v2) {
            return (v1 > v2) ? v1 : v2;
        }

        public static uint Max(uint v1, uint v2) {
            return (v1 > v2) ? v1 : v2;
        }

        public static ulong Max(ulong v1, ulong v2) {
            return (v1 > v2) ? v1 : v2;
        }

        public static float Max(float v1, float v2) {
            if (float.IsNaN(v1) || float.IsNaN(v2)) {
                return float.NaN;
            }
            return (v1 > v2) ? v1 : v2;
        }

        public static double Max(double v1, double v2) {
            if (double.IsNaN(v1) || double.IsNaN(v2)) {
                return double.NaN;
            }
            return (v1 > v2) ? v1 : v2;
        }

        #endregion

        #region Sign()

        public static int Sign(sbyte v) {
            return (v > 0) ? 1 : ((v < 0) ? -1 : 0);
        }

        public static int Sign(short v) {
            return (v > 0) ? 1 : ((v < 0) ? -1 : 0);
        }

        public static int Sign(int v) {
            return (v > 0) ? 1 : ((v < 0) ? -1 : 0);
        }

        public static int Sign(long v) {
            return (v > 0) ? 1 : ((v < 0) ? -1 : 0);
        }

        public static int Sign(float v) {
            if (float.IsNaN(v)) {
                throw new ArithmeticException("NaN");
            }
            return (v > 0) ? 1 : ((v < 0) ? -1 : 0);
        }

        public static int Sign(double v) {
            if (double.IsNaN(v)) {
                throw new ArithmeticException("NaN");
            }
            return (v > 0) ? 1 : ((v < 0) ? -1 : 0);
        }

#endregion
    
        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Acos", "_Z16System_Math_AcosPhS_S_")]
        public static extern double Acos(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Acosh", "_Z17System_Math_AcoshPhS_S_")]
        public static extern double Acosh(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Asin", "_Z16System_Math_AsinPhS_S_")]
        public static extern double Asin(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Asinh", "_Z17System_Math_AsinhPhS_S_")]
        public static extern double Asinh(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Atan", "_Z16System_Math_AtanPhS_S_")]
        public static extern double Atan(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Atan2", "_Z17System_Math_Atan2PhS_S_")]
        public static extern double Atan2(double y, double x);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Atanh", "_Z17System_Math_AtanhPhS_S_")]
        public static extern double Atanh(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Cbrt", "_Z16System_Math_CbrtPhS_S_")]
        public static extern double Cbrt(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Ceiling", "_Z19System_Math_CeilingPhS_S_")]
        public static extern double Ceiling(double a);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Cos", "_Z15System_Math_CosPhS_S_")]
        public static extern double Cos(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Cosh", "_Z16System_Math_CoshPhS_S_")]
        public static extern double Cosh(double value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Exp", "_Z15System_Math_ExpPhS_S_")]
        public static extern double Exp(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Floor", "_Z17System_Math_FloorPhS_S_")]
        public static extern double Floor(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Log", "_Z15System_Math_LogPhS_S_")]
        public static extern double Log(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Log10", "_Z17System_Math_Log10PhS_S_")]
        public static extern double Log10(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Pow", "_Z15System_Math_PowPhS_S_")]
        public static extern double Pow(double x, double y);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Sin", "_Z15System_Math_SinPhS_S_")]
        public static extern double Sin(double a);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Sinh", "_Z16System_Math_SinhPhS_S_")]
        public static extern double Sinh(double value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Sqrt", "_Z16System_Math_SqrtPhS_S_")]
        public static extern double Sqrt(double d);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Tan", "_Z15System_Math_TanPhS_S_")]
        public static extern double Tan(double a);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_Tanh", "_Z16System_Math_TanhPhS_S_")]
        public static extern double Tanh(double value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_FMod", "_Z16System_Math_FModPhS_S_")]
        private static extern double FMod(double x, double y);

        [MethodImpl(MethodImplOptions.InternalCall)]
        [GPUBCLAttribute("System_Math_ModF", "_Z16System_Math_ModFPhS_S_")]
        private static extern unsafe double ModF(double x, double* intptr);
    }
}
