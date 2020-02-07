function y = blkdiag2(varagin)

x=varagin{1};
[p2,m2]=size(x);
y=[];
for k =1:varagin{2}
    [p1,m1] = size(y);
    y=[y zeros(p1,m2);zeros(p2,m1) x];
end