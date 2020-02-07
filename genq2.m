function Q = genq2(Q1,P1,N,M,mu)
% Function to build a matrix Q that has the following form:
%      -           -                                            
%      |Q1         |                                            
%  Q = |  .        |                                            
%      |   Q1      |                                            
%      |     P1    |                                            
%      |       .   |                                            
%      |         P1|                                            
%      -           -                                            
% where Q1 is repeated N times and P1 is repeated M times.
%
% Q1 - Weight on states (mx*mx matrix)                       
% P1 - Weight on inputs (mu*mu matrix)                          
% N  - Time horizon for states
% M  - Time horizon for inputs
%                                                               
% 08.03.2001 Geir Stian Landsverk
% January 2018, Andreas L. Flåten (translated to English)
q1	= blkdiag2(Q1,N);
p1	= blkdiag2(P1,M);

Q	= blkdiag(q1,p1); 