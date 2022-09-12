function A3_Vorlage_Visualisierung_BA_Trajektorie(T_i, T_a)

%% Visualisierung der Trajektorien T_i und T_a:

hold on
axis equal
axis([-50 +50 -5 105])

plot( T_a(1,:), T_a(2,:), 'b' , T_i(1,:), T_i(2,:), 'b');
plot( -T_a(1,:), T_a(2,:), 'b', -T_i(1,:), T_i(2,:), 'b');

xlabel("x-Achse")
ylabel("y-Achse")




% Zusätzlich
T1_Plot_Ego_Fahrzeug;
