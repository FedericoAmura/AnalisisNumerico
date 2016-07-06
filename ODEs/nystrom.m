function [t,x,v] =nystrom(f,t0,tf,x0,v0,n,eps)
      h=(tf-t0)/n;
      t=t0:h:tf;
      x=zeros(n+1,1); %reserva memoria para n+1 element(i)os del vect(i)or x(i)
      v=zeros(n+1,1);
      x(1)=x0; v(1)=v0;
      
      %RK4 para el segundo valor
      k1=h*v(1);
      l1=h*f(t(1),x(1),v(1));
      k2=h*(v(1)+l1/2);
      l2=h*f(t(1)+h/2,x(1)+k1/2,v(1)+l1/2);
      k3=h*(v(1)+l2/2);
      l3=h*f(t(1)+h/2,x(1)+k2/2,v(1)+l2/2);
      k4=h*(v(1)+l3);
      l4=h*f(t(1)+h,x(1)+k3,v(1)+l3);
      
      x(2)=x(1)+(k1+2*k2+2*k3+k4)/6;
      v(2)=v(1)+(l1+2*l2+2*l3+l4)/6;
      
      %Ahora Nystrom
      for i=2:n
        x(i+1)=(-x(i-1)/h^2+2*x(i)/h^2-eps*x(i-1)/(2*h)+eps*x(i)^2*x(i-1)/(2*h)-x(i))/(1/h^2-eps/(2*h)+eps*x(i)^2/(2*h));
        v(i+1)=(x(i+1)-x(i-1))/(2*h);
      end
      
end