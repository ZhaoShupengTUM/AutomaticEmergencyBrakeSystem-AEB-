%% Plotten des Ego Fahrzeuges
%% Abmessung Ego Fahrzeug
l = 4;
b_ego_ganz = 1.983;
b = b_ego_ganz/2; %halbe Fahrzeugbreit

%% Berechnungen
% Randpunkte Viereck
p4_x = [-b,+b,+b,-b];
p4_y = [0,0,-l,-l];

% Randpunkte Dreieck
p3_x = [0,-b,+b];
p3_y = [0,-l/3,-l/3];

%% Plotten
hold on
axis equal
fill(p4_x, p4_y, 'k')
fill(p3_x, p3_y, 'w')