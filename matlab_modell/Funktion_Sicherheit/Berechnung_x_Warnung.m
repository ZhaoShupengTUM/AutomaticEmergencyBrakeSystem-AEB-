function [x_warn] = Berechnung_x_Warnung(v_fahr, sensor_setup)
 n = size(v_fahr);
 x_warn = zeros(n(1), n(2));
 m = 1;
 
if sensor_setup == 1  %Opel
    % auto parameters
    t_warn = 0.5; 
    for v = v_fahr
        x_w = v/3.6 * t_warn;  %notice that the unit must ba changed to m/s!!
        if v < 15  %if the speed is low
            x_warn(m) = (v/3.6)^2/18+x_w;
        else          
            x_k =  (v/3.6)^2/8 - (15/3.6)^2/8 ; %comfortable brake distance
            x_v = (15/3.6)^2/18;  %full brake distance
            x_warn(m) = x_k + x_w + x_v;  %total distance
        end
        m = m + 1;      
    end
    
elseif sensor_setup == 2 %Mercedes
    t_warn = 0.5;
   for v = v_fahr
        x_w = v/3.6 * t_warn;  %warning time distance
        if v < 30  %if the speed is low
            x_warn(m) = (v/3.6)^2/18+x_w;
        else          
            x_k =  (v/3.6)^2/8 - (30/3.6)^2/8 ; %comfortable brake distance
            x_v = (30/3.6)^2/18;  %full brake distance
            x_warn(m) = x_k + x_w + x_v;  %total distance
        end
        m = m + 1;
   end
   
else
    disp("Bitte richtig sensor-sets Name eintippen.");
    
end

