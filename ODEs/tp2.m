clear;
t0=0;     %Tiempo inicial
tf=39;    %Tiempo final
a=1;      %Alfa, V inicial
b=0;      %Beta, V' inicial
n=500;    %Cantidad de pasos

%Epsilon
eps=input('epsilon: ');

%Funcion para los metodos Euler, RK y Nystrom
f=@(t,v,vp) eps*(1-v^2)*vp-v;

%Resoluciones
%EULER
[t,ve,vpe] = euler(f,t0,tf,a,b,n);
%RK2
[t,vrk2,vprk2] = rk_2(f,t0,tf,a,b,n);
%RK4
[t,vrk4,vprk4] = rk_4(f,t0,tf,a,b,n);
%Nystrom
[t,vn,vpn] = nystrom(f,t0,tf,a,b,n,eps);
%ODE23
f23 = @(t,v23) [v23(2);eps*(1-v23(1)^2)*v23(2)-v23(1)]; % v23(1) es v, v23(2) es vp
[t23, v23] = ode23(f23,[0 tf],[a b]);
%ODE45
f45=@(t,v45) [v45(2);eps*(1-v45(1)^2)*v45(2)-v45(1)]; % v45(1) es v, v45(2) es vp
[t45,v45]=ode45(f45,[0, tf],[a b]);

%Dibujos
hold on
clf;
%V(t) vs t
figure(1);
plot(t,ve,'r',t,vrk2,'g',t,vrk4,'b',t,vn,'m',t23,v23(:,1),'y',t45,v45(:,1),'c');
title('TP2 V(t) vs t');
xlabel('t');
ylabel('V(t)');
legend('Euler','RK2','RK4','Nystrom','ode23','ode45');
%Vp(t) vs t
figure(2);
plot(t,vpe,'r',t,vprk2,'g',t,vprk4,'b',t,vpn,'m',t23,v23(:,2),'y',t45,v45(:,2),'c');
title('TP2 Vp(t) vs t');
xlabel('t');
ylabel('Vp(t)');
legend('Euler','RK2','RK4','Nystrom','ode23','ode45');
%V(t) vs Vp(t)
figure(3);
plot(ve,vpe,'r',vrk2,vprk2,'g',vrk4,vprk4,'b',vn,vpn,'m',v23(:,1),v23(:,2),'y',v45(:,1),v45(:,2),'c');
title('TP2 Vp(t) vs V(t)');
xlabel('V(t)');
ylabel('Vp(t)');
legend('Euler','RK2','RK4','Nystrom','ode23','ode45');
hold off
