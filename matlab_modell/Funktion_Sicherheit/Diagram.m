figure;

v = 0:0.1:100;
x_fehl = Berechnung_x_Fehlausloesung(v);
x_warn_1 = Berechnung_x_Warnung(v,1);
x_warn_2 = Berechnung_x_Warnung(v,2);

plot(v,x_fehl,"k",v, x_warn_1, "r", v,x_warn_2, "b");

legend("Abstand bei Reaktion des sportlichen Fahrers", "Ausloeseabstand Opel", "Ausloeseabstand Mercedes","location","northwest");

xlabel("Versuchsgeschwindigkeit in km/h")
ylabel("Abstand zum Target in m")

%for i=1:length(v)
 %   x(i) = v(i) +0.1;
%end