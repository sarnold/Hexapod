function [boolean] = isEqualPos(pos, center)
%If two positions are fairly close to each other it returns true, else
%false. fairly close equals square of 20mm.

boolean = 1;

for i = 1:2
    if pos(i) > center(i) + 10 || pos(i) < center(i) -10
        boolean = 0;
        break;
    end
end
end