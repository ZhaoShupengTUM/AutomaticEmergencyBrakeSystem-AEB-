function [x_fehl] = Berechnung_x_Fehlausloesung(v)

a_s = 5;
x_buffer = 3;
x_fehl = (v/3.6).^2/(2*a_s) + x_buffer; %the total distance

end

