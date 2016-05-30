clear all;
amp=5000;% signal amplification
nscans=26*28;% number of scans

chirp_pos=[];
chirp_neg=[];
flat=[];

%get scaling coeffiecients
%%%%%%%%%%%%%%%%%%%%%%%%%%
%xinterval=1;% horizontal sampling interval (sec)
%x0=0;% time of first point in waveform (sec)
% yconvert=2.0E-2;% vertical scale factor
xinterval=importdata('scope_xinterval.txt');
x0=importdata('scope_x0.txt');
yconvert=importdata('scope_yscaling.txt');

%get data
%%%%%%%%%%%%%%%%%%%%%%%%%%
j=1;
for i=7:nscans+6
    fname = 'scope_data';
    fname = strcat(fname,int2str(i));
    fname = strcat(fname,'.txt');
    fid = fopen(fname,'r'); 
    [buf,count] = fread(fid, 'int8');
    fclose(fid);
    buf=buf*yconvert/amp;
    eval(sprintf('data%d=buf;',j));
    matrix(:,j)=buf;
    j=j+1;
    buf=0;
end

%time axis
%%%%%%%%%%%%%%%%%%%%%%%%%%
for i=1:length(data1)
    t(i)=xinterval*(i-1);
end

%Dispatch data
%%%%%%%%%%%%%%%%%%%%%%%%%%
for percent=20
for n=0:26:nscans-26
   for m=0:6:18 
        chirp_pos=[chirp_pos;matrix(:,n+m+1).'];
        chirp_pos=[chirp_pos;matrix(:,n+m+2).'];
        flat=[flat;matrix(:,n+m+3).'];
        flat=[flat;matrix(:,n+m+4).'];
        chirp_neg=[chirp_neg;matrix(:,n+m+5).'];
        chirp_neg=[chirp_neg;matrix(:,n+m+6).'];
   end
   flat=[flat;matrix(:,n+m+7).'];
   flat=[flat;matrix(:,n+m+8).'];
end
figure;
plot(trimmean(flat,percent)-mean(trimmean(flat(:,1:1000),percent)),'o');
hold on;
plot(trimmean(chirp_pos,percent)-mean(trimmean(chirp_pos(:,1:1000),percent)),'+');
plot(trimmean(chirp_neg,percent)-mean(trimmean(chirp_neg(:,1:1000),percent)));
hold off;
end
% 
% figure;
% %plot all data
% %%%%%%%%%%%%%%%%%%%%%%%%%
% 
%     for k=l:nscans
%         eval(sprintf('buf=data%d;',k));
%         plot(t+x0,buf,'color',[0,0,0 ]+0.7);
%         xlabel('Time, sec');
%         ylabel('Amplitude, V')
%         hold on
%     end
% 
% 
% %plot average data
% %%%%%%%%%%%%%%%%%%%%%%%%%%
% % plot(t+x0,sum(matrix')/(j-1),'color',[0,0,0 ],'LineWidth',2);
% 
% 
% 
% 
% m=1;
% l=1;
% k=1;
% for l=1:3
%     for k=l:3:nscans
%         xxx(:,m)=matrix(:,k);
%         m=m+1;
%     end
%     m=1;
%     buf=trimmean(xxx',0);
%     buf=buf-buf(10);
%     plot(t+x0,buf,'color',[0,0,0],'LineWidth',2);
%     xlabel('Time, sec');
%     ylabel('Amplitude, V');
%     hold on
% end
% % axis([-0.01 0.04 -0.03 0.005]);
% hold off

