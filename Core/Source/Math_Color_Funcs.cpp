#include "../Internal/stdafx.h"
#include "../Include/Math_Color.h"
#include "../Include/Math_Funcs.h"

namespace CB{
	namespace Math{
		const CColor	FromABGR(const uint32 uIndex){
			byte* pColor = (byte*)&uIndex;

			CColor cResult;
			cResult.Set(pColor[3], pColor[2], pColor[1], pColor[0]);

			return cResult;
		}

		const CColor	FromARGB(const uint32 uIndex){
			byte* pColor = (byte*)&uIndex;

			CColor cResult;
			cResult.Set(pColor[1], pColor[2], pColor[3], pColor[0]);
	
			return cResult;
		}

		const CColor	FromBGRA(const uint32 uIndex){
			byte* pColor = (byte*)&uIndex;

			CColor cResult;
			cResult.Set(pColor[2], pColor[1], pColor[0], pColor[3]);

			return cResult;
		}

		const CColor	FromRGBA(const uint32 uIndex){
			byte* pColor = (byte*)&uIndex;

			CColor cResult;
			cResult.Set(pColor[0], pColor[1], pColor[2], pColor[3]);

			return cResult;
		}

		// Conversion RGB vers HSV.

		const CColorHSV RGB2HSV(const CColor& Color){
			CColorHSV	dest;
			float32	min, max, delta;

			min = Min(Color.Red, Color.Green, Color.Blue);
			max = Max(Color.Red, Color.Green, Color.Blue);

			dest.V = max;

			if(max == 0.0f){
				dest.S = 0.0f;
				dest.H = 0.0f;
			}
			else{
				delta = max - min;
				dest.S = delta / max;
				if(Color.Red == max){
					dest.H = (Color.Green - Color.Blue) / delta;
				}
				else if(Color.Green == max){
					dest.H = 2.0f + (Color.Blue - Color.Red) / delta;
				}
				else{
					dest.H = 4.0f + (Color.Red - Color.Green) / delta;
				}

				dest.H *= 60.0f;
				if(dest.H < 0.0f){
					dest.H += 360.0f;
				}
				dest.H /= 360.0f;
			}

			return dest;
		}

		// Conversion HSV vers RGB.

		const CColor	HSV2RGB(const CColorHSV& Color){
			CColor		dest;
			CColorHSV	src;
			int		i;
			float32	f,v,p,q,t;

			src.H = Clamp01(Color.H) * 360.0f;
			src.S = Clamp01(Color.S);
			src.V = Clamp01(Color.V);

			if(src.S == 0.0f){
				dest.Set(src.V, src.V, src.V);
			}
			else{
				if(src.H == 360.0f){
					src.H = 0.0f;
				}
				src.H /= 60.0f;
				i = (int)src.H;
				f = src.H - i;

				v = src.V;
				p = src.V * (1.0f - src.S);
				q = src.V * (1.0f - (src.S * f));
				t = src.V * (1.0f - (src.S * (1.0f - f)));

				switch(i){
				case 0:	dest.Set(v, t, p);	break;
				case 1:	dest.Set(q, v, p);	break;
				case 2:	dest.Set(p, v, t);	break;
				case 3:	dest.Set(p, q, v);	break;
				case 4:	dest.Set(t, p, v);	break;
				case 5:	dest.Set(v, p, q);	break;
				}
			}
			return dest;
		}
	}
}