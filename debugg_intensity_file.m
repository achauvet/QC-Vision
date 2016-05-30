i=1;
j=3;
var=0;

var(1:2)=int(1:2);
for i=3:4450
    if int(i)~=int(i-2)
        var(j)=int(i);
        i=i+1;
        j=j+1;
    else
        i=i+1;
    end
end
