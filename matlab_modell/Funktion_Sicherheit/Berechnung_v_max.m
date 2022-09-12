function Berechnung_v_max(Sensor_set)

syms v;
if Sensor_set == 1
    eq = (v/3.6)*0.5 + (v/3.6)^2/8 - (15/3.6)^2/8 + (15/3.6)^2/18 - ((v/3.6)^2/(2*5)+3) == 0;
    v_solve = solve(eq);
    v_max = max(v_solve);
    fprintf('\nDie maximale unfallvermeidende Geschwindigkeit bei SensorSetup %.0f betraegt %.1f.\n',1,v_max);

%Opel
elseif Sensor_set == 2
    eq = (v/3.6)*0.5 + (v/3.6)^2/8 - (30/3.6)^2/8 + (30/3.6)^2/18 - ((v/3.6)^2/(2*5)+3) == 0;
    v_solve = solve(eq);
    v_max = max(v_solve);
    fprintf('\nDie maximale unfallvermeidende Geschwindigkeit bei SensorSetup %.0f betraegt %.1f.\n',2,v_max);

end

