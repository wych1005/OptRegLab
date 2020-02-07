function y = blkdiag(varagin)

y=[];
for k =1:nargin
    x=varagin{k};
    [p1,m1] = size(y); [p2,m2] = size(x);
    y=[y zeros(p1,m2);zeros(p2,m1) x];
end