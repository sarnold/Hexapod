function r = interpolateR(radius, height)
%Function to use for linear interpolation of the radius values used in
%boundaries and deafult position. The result is a r value inbetween to
%distinct heights.

k = floor(height/10);
if k == 15
    r = radius(k);
else
    diff = radius(k+1) - radius(k);
    extra = diff * ((height/10)-k);
    r = radius(k) + extra;
end

end