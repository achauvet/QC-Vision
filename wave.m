
figure;
for i=0:10
    
    fileID = fopen(['scope_data',int2str(i),'.txt']);
    C = fread(fileID,2500,'int8');
    %data=C{1,1}.';
    fclose(fileID);
    plot(C);
    hold on
end