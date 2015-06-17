function boundary = getBoundary()
%Bouandarys for the legs in in radius. Inner and outer radius are boundarys
%that legs could be prevented from overextending. data is sorted by
%boundaries at different heights in mm as in [0 10 20... 150]


boundary = [0 158 153 148 141 131 119 102 69  5   5   5   5   5   5   5; 
            0 240 234 231 227 224 221 214 207 200 193 183 173 167 158 139];

end