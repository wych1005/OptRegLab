
%% Initialization and model definition
init; % Change this to the init file corresponding to your helicopter

global N alpha lambda_t beta mx
alpha=0.2;
beta=20;
lambda_t=2*pi/3;


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
pk      = 30*pi/180;
ul 	    = [-pk; -inf];                   % Lower bound on control -- ul
uu 	    = [pk; inf];                     % Upper bound on control -- uu

xl(1:mx,1)    = -Inf*ones(mx,1);         % Lower bound on states (no bound)
xu(1:mx,1)    = Inf*ones(mx,1);          % Upper bound on states (no bound)
xl(3)   = ul(1);                         % Lower bound on state x3
xu(3)   = uu(1);                         % Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]       =  gen_constraints(N,M,xl,xu,ul,uu); % hint: gen_constraints
vlb(N*mx+M*mu)  = 0;                    % We want the last input to be zero
vub(N*mx+M*mu)  = 0;                    % We want the last input to be zero
nonlcon = [];
% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
q = 1;
Q1 = zeros(mx,mx);
Q1(1,1) = 2;                            % Weight on state x1
Q1(2,2) = 0;                            % Weight on state x2
Q1(3,3) = 0;                            % Weight on state x3
Q1(4,4) = 0;                            % Weight on state x4
q1 = 0.1; q2 = q1;
P1 = diag([q1 q2]);                                % Weight on input
Q = gen_q(Q1,P1,N,M);                                  % Generate Q, hint: gen_q
c = zeros(N*mx+M*mu, 1);                                  % Generate c, this is the linear constant term in the QP

%% Generate system matrixes for linear model
Aeq = gen_aeq(A1,B1,N,mx,mu);             % Generate A, hint: gen_aeq
beq = zeros(size(Aeq,1),1); 
beq(1:mx) = A1 * x0;             % Generate b
G = 2*genq2(Q1,P1,N,M,mu);

%% Solve QP problem with linear model
f = @(z) 1/2*z'*G*z;
opt = optimoptions('fmincon','Algorithm','sqp','MaxFunEvals',40000);
tic
[Z, ZVAL, EXITFLAG] = fmincon(f, z0, [], [], Aeq, beq, vlb, vub, @constraints, opt);
toc

% Calculate objective value
phi1 = 0.0;
PhiOut = zeros(N*mx+M*mu,1);
for i=1:N*mx+M*mu
  phi1=phi1+Q(i,i)*z(i)*z(i);
  PhiOut(i) = phi1;
end

%% Extract control inputs and states
u1  = [Z(N*mx+1:2:N*mx+M*mu);Z(N*mx+M*mu-1)];
u2  = [Z(N*mx+2:2:N*mx+M*mu);Z(N*mx+M*mu)]; % Control input from solution

x1 = [x0(1);Z(1:mx:N*mx)];              % State x1 from solution
x2 = [x0(2);Z(2:mx:N*mx)];              % State x2 from solution
x3 = [x0(3);Z(3:mx:N*mx)];              % State x3 from solution
x4 = [x0(4);Z(4:mx:N*mx)];              % State x4 from solution
x5 = [x0(5);Z(5:mx:N*mx)];
x6 = [x0(6);Z(6:mx:N*mx)];

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

u = [u1 u2];
x_opt = [x1 x2 x3 x4 x5 x6];
%% Plotting
t = 0:delta_t:delta_t*(length(u1)-1);

% newu=zeros(141,2);
% newu(:,1)=t';
% newu(:,2)=u;

figure(2)
subplot(711)
stairs(t,u),grid
ylabel('u')
subplot(712)
plot(t,x1,'m',t,x1,'mo'),grid
ylabel('lambda')
subplot(713)
plot(t,x2,'m',t,x2','mo'),grid
ylabel('r')
subplot(714)
plot(t,x3,'m',t,x3,'mo'),grid
ylabel('p')
subplot(715)
plot(t,x4,'m',t,x4','mo'),grid
ylabel('pdot')
subplot(716)
plot(t,x5,'m',t,x5','mo'),grid
ylabel('e')
subplot(717)
plot(t,x6,'m',t,x6','mo'),grid
ylabel('edot')
xlabel('tid (s)')

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
%seqfeed(:,7)=t';


%% LQR cost function
q_entries = [5 1 1 0.5 30 10];    
Qlqr = diag(q_entries);
Rlqr = diag([2 2]);

Klqr = dlqr(A1, B1, Qlqr, Rlqr);
Klqr_t = Klqr';


