function [c,ceq] = constraints(z)
    
    global N alpha lambda_t beta mx
    c = zeros(N,1);
    for k=1:N
        c(k) = alpha*exp(-beta*(z(1+(k-1)*mx)-lambda_t)^2) - z(5+(k-1)*mx);
    end
    ceq = [];
end