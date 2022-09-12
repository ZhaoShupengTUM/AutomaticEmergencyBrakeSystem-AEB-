% Script to test [x,y] = stationaryLeftCurve(s, R)

%% Full circle
% Test, ob x und y innerhalb des Zielkreises sind
R = 10;
s = 2*pi*R;
[x,y] = stationaryLeftCurve(s,R);
assert(max(x)<=R, 'x-value too large')
assert(min(x)>=-R, 'x-value too small')
assert(max(y)<=2*R, 'y-value too large')
assert(min(y)>=0, 'y-value too small')

tolerance = R*0.03;
assert(is_there_a_point_at(0,2*R,x,y,tolerance), 'values at pi not found')
assert(is_there_a_point_at(R,R,x,y,tolerance), 'values at pi/2 not found')
assert(is_there_a_point_at(R,2*R,x,y,tolerance)==false, 'no values at R,2R')

%% Partial circle
% Test, ob bei gewünschter Viertelkurve kein Halbkreis erzeugt wird
R = 10;
s = (1/2)*pi*R;
[x,y] = stationaryLeftCurve(s,R);
tolerance = R*0.03;
assert(is_there_a_point_at(0,2*R,x,y,tolerance)==false, ...
    'there should not be a value at (0,2R)')

%% Display "SUCCESS"
% Wenn die Funktion bis hierher durchläuft, ist kein Test gescheitert
disp('SUCCESSFUL');

%% Test function
% Funktion testet, ob in (x,y) bei (x_Point, y_Point) ein Punkt liegt
function returnBool = is_there_a_point_at(x_Point,y_Point,x,y,tolerance)
returnBool = false;
for iterator = 1:length(x)
    if abs(x(iterator)-x_Point)<=tolerance && ...
            abs(y(iterator)-y_Point)<=tolerance
        %disp(x(iterator));
        %disp(y(iterator));
        returnBool = true;
    end
end
end