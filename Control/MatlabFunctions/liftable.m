function [lift] = liftable(legsInAir, legID)
%All legs can't be lifted simultaneously. This function checks if a given
%leg can be lifted in company with already lifted legs.


%Assume leg can be lifted
lift = 1;

%Rule out the opposite. Legs not allowed in air simultaneously are legs
%behind or infront of eachother. ALso legs on direct opposite sides are not
%allowed in air simultaneously.
switch legID
    case 1
        if legsInAir(2) == 1 || legsInAir(4) == 1
            lift = 0;
        end
    case 2
        if legsInAir(5) == 1 || legsInAir(1) == 1 || legsInAir(3) == 1
            lift = 0;
        end
    case 3
        if legsInAir(6) == 1 || legsInAir(2) == 1
            lift = 0;
        end
    case 4
        if legsInAir(1) == 1 || legsInAir(5) == 1
            lift = 0;
        end
    case 5
        if legsInAir(2) == 1 || legsInAir(4) == 1 || legsInAir(6) == 1
            lift = 0;
        end
    case 6
        if legsInAir(3) == 1 || legsInAir(5) == 1
            lift = 0;
        end
    %In case of unknown bug, don't lift leg.    
    otherwise
        lift = 0;
end
end