%%k0 = Tn0*kn

theta = deg2rad([100 1 144 155 166])

DH = [  36  -pi/2   0       theta(1);
        0   pi/2    60      theta(2)+pi/2;
        30  -pi/2   290     theta(3);
        20  pi/2    0       theta(4);
        0   0       75+290  theta(5)]

%%Tn0 =  [nx  sx  ax  px;
   %     ny  sy  ay  py;
    %    nz  sz  az  pz;
     %   0   0   0   1]