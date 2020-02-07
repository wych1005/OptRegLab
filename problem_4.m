
%% Initialization and model definition
init; % Change this to the init file corresponding to your helicopter

% Discrete time system model. x = [lambda r p p_dot]'
Ac = [0        1        0        0        0        0; 
     0        0      -K_2       0        0        0; 
     0        0        0        1        0        0; 
     0        0  -K_1*K_pp  -K_1*K_pd    0        0; 
     0        0        0        0        0        1; 
     0        0        0        0   -K_3*K_ep   -K_3*K_ed];

Bc = [0 0 0 K_1*K_pp 0 0; 0 0 0 0 0 K_3*K_ep]';
delta_t	= 0.25; % sampling time
A1 = eye(6)+ delta_t * Ac;
B1 = delta_t * Bc;

% Number of states and inputs
mx = size(A1,2); % Number of states (number of columns in A)
mu = size(B1,2); % Number of inputs(number of columns in B)

% Initial values
x1_0 = pi;                               % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x5_0 = 0;                               % e
x6_0 = 0;                               % e_dot
x0 = [x1_0 x2_0 x3_0 x4_0 x5_0 x6_0]';           % Initial values

% Time horizon and initialization
N  = 100;                                  % Time horizon for states
M  = N;                                 % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;                                 % Initial value for optimization

% Bounds
ul 	   = -1*30*pi/180  ;                   % Lower bound on control
uu 	    = 30*pi/180 ;                   % Upper bound on control

xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl(3)   = ul;                           % Lower bound on state x3
xu(3)   = uu;                           % Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]       =  gen_constraints(N,M,xl,xu,ul,uu); % hint: gen_constraints
vlb(N*mx+M*mu)  = 0;                    % We want the last input to be zero
vub(N*mx+M*mu)  = 0;                    % We want the last input to be zero

% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
q = 1;
Q1 = zeros(mx,mx);
Q1(1,1) = 2;                            % Weight on state x1
Q1(2,2) = 0;                            % Weight on state x2
Q1(3,3) = 0;                            % Weight on state x3
Q1(4,4) = 0;                            % Weight on state x4
P1 = 2*q;                                % Weight on input
Q = gen_q(Q1,P1,N,M);                                  % Generate Q, hint: gen_q
c = zeros(N*mx+M*mu, 1);                                  % Generate c, this is the linear constant term in the QP

%% Generate system matrixes for linear model
Aeq = gen_aeq(A1,B1,N,mx,mu);             % Generate A, hint: gen_aeq
beq = zeros(600,1); 
beq(1:mx) = A1 * x0;             % Generate b

%% Solve QP problem with linear model

%f = zeros(500,1);
G = 2*genq2(Q1,P1,N,M,mu);

%G = 2*gen_q(Q1,P1,N,M);
opt = optimoptions('fmincon', 'Algorithm', 'sqp', 'MaxFunEvals', 40000);
f = @(z) 1/2*z'*G*z;
tic
% [z,lambda] = quadprog(Q,c,[],[],Aeq,beq,vlb,vub, x0); % hint: quadprog. Type 'doc quadprog' for more info 
[Z, ZVAL, EXITFLAG] = fmincon(f, z0, [], [], Aeq, beq, vlb, vub, @constraints, opt);
t1=toc;

% Calculate objective value
phi1 = 0.0;
PhiOut = zeros(N*mx+M*mu,1);
for i=1:N*mx+M*mu
  phi1=phi1+Q(i,i)*z(i)*z(i);
  PhiOut(i) = phi1;
end

%% Extract control inputs and states
u1  = [z(N*mx+1:N*mx+M*mu);z(N*mx+M*mu-1)];
u2  = [z(N*mx+2:N*mx+M*mu);z(N*mx+M*mu)]; % Control input from solution

x1 = [x0(1);z(1:mx:N*mx)];              % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];              % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];              % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];              % State x4 from solution
x5 = [x0(5);z(5:mx:N*mx)];
x6 = [x0(6);z(6:mx:N*mx)];

num_variables = 10/delta_t;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u1   = [zero_padding; u1; zero_padding];
u2   = [zero_padding; u2; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];

%% Plotting
t = 0:delta_t:delta_t*(length(u)-1);

% newu=zeros(141,2);
% newu(:,1)=t';
% newu(:,2)=u;

figure(2)
subplot(511)
stairs(t,u),grid
ylabel('u')
subplot(512)
plot(t,x1,'m',t,x1,'mo'),grid
ylabel('lambda')
subplot(513)
plot(t,x2,'m',t,x2','mo'),grid
ylabel('r')
subplot(514)
plot(t,x3,'m',t,x3,'mo'),grid
ylabel('p')
subplot(515)
plot(t,x4,'m',t,x4','mo'),grid
xlabel('tid (s)'),ylabel('pdot')

% data_sequence=zeros(141,5);
% data_sequence(:,1)=t';
% data_sequence(:,2)=u;
% data_sequence(:,3)=x1;
% data_sequence(:,4)=x2;
% data_sequence(:,5)=x3;
% data_sequence(:,6)=x4;

seqfeed=zeros(181,4);
seqfeed(:,1)=x1;
seqfeed(:,2)=x2;
seqfeed(:,3)=x3;
seqfeed(:,4)=x4;
seqfeed(:,5)=x5;
seqfeed(:,6)=x6;

%% LQR cost function
q_entries = [5 1 3 1];
Qlqr = diag(q_entries);
Rlqr = 1;

Klqr = dlqr(A1, B1, Qlqr, Rlqr);
Klqr_t = Klqr';

%% fmincon
lambda_t = (2/3)*pi;
%obj_fun = 
