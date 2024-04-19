from tkinter import *
import json
import math


my_width=800
my_height=400
my_shift=50
arr=[]

with open('test.json','r') as f:
    data=json.load(f)
    arr=data["arr"]

count=len(arr)
max_v=-273
for i in arr:
    if i[1]>max_v:
        max_v=i[1]
        
min_v=100
for i in arr:
    if i[1]<min_v:
        min_v=i[1]
print("{} {}".format(min_v,max_v))

    



tk=Tk()
tk.title(data["title"])
tk.resizable(0,0)
tk.geometry("{}x{}+600+100".format(my_width,my_height))
tk.attributes("-topmost",True)
canvas=Canvas(tk,width=my_width,height=my_height,bd=0,highlightthickness=0)
canvas.pack()
tk.update()


key_word=[i for i in data["title"].split(' ')]
print(key_word)

zero=my_height/2
d=my_height/2-my_shift
step_x=(my_width-2*my_shift)/count
delta=max_v-min_v
k=0

if max_v<0:
    k=d/min_v
    s=abs(min_v)/2
else:
    if min_v>0:
        k=d/max_v
        s=max_v/2
    else:
        if max_v>abs(min_v):
            k=d/max_v
            s=max_v/2
        else:
            k=d/abs(min_v)
            s=abs(min_v)/2


    
line_x = canvas.create_line(my_shift,my_height/2,
                            my_width-my_shift,my_height/2,
                            fill="blue",width=2,arrow=LAST) 
line_y = canvas.create_line(my_shift,my_height-my_shift,
                            my_shift,my_shift,
                            fill="blue",width=2,arrow=LAST)


canvas.create_text(20,my_shift+d/2,text="{}".format(s))
canvas.create_text(20,zero+d/2,text="-{}".format(s))
canvas.create_text(my_shift,20,text="Temperature,C")



canvas.create_text(my_width-my_shift,zero+20,text="{}(s)".format(key_word[len(key_word)-1]))
canvas.create_text(my_width/2,zero+20,text="{}".format(count/2))

canvas.create_line(my_width/2,zero+5,my_width/2,zero-5,fill="blue",width=2)

canvas.create_line(my_shift-5,my_shift+d/2,my_shift+5,my_shift+d/2,fill="blue",width=2)
canvas.create_line(my_shift-5,zero+d/2,my_shift+5,zero+d/2,fill="blue",width=2)


x=my_shift
y=my_height/2
for item in arr:
    x+=step_x
##    temp=zero-d*item[1]/max_v
##    if delta==0:
##        temp=zero-d/2
##    else:
##        temp=zero-(abs(item[1])-abs(min_v))*d/delta
    #temp=zero-item[1]
    rectangle_id = canvas.create_rectangle(x,zero-item[1]*k,x+2,zero-item[1]*k+2,width=1,outline="red",fill="red")

tk.mainloop()
