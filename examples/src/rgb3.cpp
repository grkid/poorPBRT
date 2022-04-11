#include "rgb3.h"
#include "xyz3.h"
#include "SampledSpectrum.h"

xyz3 rgb3::toXyz3() const
{   
    xyz3 xyz;
    xyz[0] = 0.412453f * e[0] + 0.357580f * e[1] + 0.180423f * e[2];
    xyz[1] = 0.212671f * e[0] + 0.715160f * e[1] + 0.072169f * e[2];
    xyz[2] = 0.019334f * e[0] + 0.119193f * e[1] + 0.950227f * e[2];
    return xyz;
}

SampledSpectrum rgb3::toSampledSpectrum(SpectrumType type) const
{
    SampledSpectrum r;
    if (type == SpectrumType::reflectance) {
        // Convert reflectance spectrum to rgb
        if (e[0] <= e[1] && e[0] <= e[2]) {
            // Compute reflectance _SampledSpectrum_ with _rgb[0]_ as minimum
            r += e[0] * SampledSpectrum::rgbRefl2SpectWhite;
            if (e[1] <= e[2]) {
                r += (e[1] - e[0]) * SampledSpectrum::rgbRefl2SpectCyan;
                r += (e[2] - e[1]) * SampledSpectrum::rgbRefl2SpectBlue;
            }
            else {
                r += (e[2] - e[0]) * SampledSpectrum::rgbRefl2SpectCyan;
                r += (e[1] - e[2]) * SampledSpectrum::rgbRefl2SpectGreen;
            }
        }
        else if (e[1] <= e[0] && e[1] <= e[2]) {
            // Compute reflectance _SampledSpectrum_ with _rgb[1]_ as minimum
            r += e[1] * SampledSpectrum::rgbRefl2SpectWhite;
            if (e[0] <= e[2]) {
                r += (e[0] - e[1]) * SampledSpectrum::rgbRefl2SpectMagenta;
                r += (e[2] - e[0]) * SampledSpectrum::rgbRefl2SpectBlue;
            }
            else {
                r += (e[2] - e[1]) * SampledSpectrum::rgbRefl2SpectMagenta;
                r += (e[0] - e[2]) * SampledSpectrum::rgbRefl2SpectRed;
            }
        }
        else {
            // Compute reflectance _SampledSpectrum_ with _rgb[2]_ as minimum
            r += e[2] * SampledSpectrum::rgbRefl2SpectWhite;
            if (e[0] <= e[1]) {
                r += (e[0] - e[2]) * SampledSpectrum::rgbRefl2SpectYellow;
                r += (e[1] - e[0]) * SampledSpectrum::rgbRefl2SpectGreen;
            }
            else {
                r += (e[1] - e[2]) * SampledSpectrum::rgbRefl2SpectYellow;
                r += (e[0] - e[1]) * SampledSpectrum::rgbRefl2SpectRed;
            }
        }
        r *= .94;
    }
    else {
        // Convert illuminant spectrum to e
        if (e[0] <= e[1] && e[0] <= e[2]) {
            // Compute illuminant _SampledSpectrum_ with _rgb[0]_ as minimum
            r += e[0] * SampledSpectrum::rgbIllum2SpectWhite;
            if (e[1] <= e[2]) {
                r += (e[1] - e[0]) * SampledSpectrum::rgbIllum2SpectCyan;
                r += (e[2] - e[1]) * SampledSpectrum::rgbIllum2SpectBlue;
            }
            else {
                r += (e[2] - e[0]) * SampledSpectrum::rgbIllum2SpectCyan;
                r += (e[1] - e[2]) * SampledSpectrum::rgbIllum2SpectGreen;
            }
        }
        else if (e[1] <= e[0] && e[1] <= e[2]) {
            // Compute illuminant _SampledSpectrum_ with _rgb[1]_ as minimum
            r += e[1] * SampledSpectrum::rgbIllum2SpectWhite;
            if (e[0] <= e[2]) {
                r += (e[0] - e[1]) * SampledSpectrum::rgbIllum2SpectMagenta;
                r += (e[2] - e[0]) * SampledSpectrum::rgbIllum2SpectBlue;
            }
            else {
                r += (e[2] - e[1]) * SampledSpectrum::rgbIllum2SpectMagenta;
                r += (e[0] - e[2]) * SampledSpectrum::rgbIllum2SpectRed;
            }
        }
        else {
            // Compute illuminant _SampledSpectrum_ with _rgb[2]_ as minimum
            r += e[2] * SampledSpectrum::rgbIllum2SpectWhite;
            if (e[0] <= e[1]) {
                r += (e[0] - e[2]) * SampledSpectrum::rgbIllum2SpectYellow;
                r += (e[1] - e[0]) * SampledSpectrum::rgbIllum2SpectGreen;
            }
            else {
                r += (e[1] - e[2]) * SampledSpectrum::rgbIllum2SpectYellow;
                r += (e[0] - e[1]) * SampledSpectrum::rgbIllum2SpectRed;
            }
        }
        r *= .86445f;
    }
    return r.clamp();
}
