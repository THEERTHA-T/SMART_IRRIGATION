import re
from django.shortcuts import render
from django.http import HttpResponse 

# Create your views here.
#def index(request): #view named index
 #   return HttpResponse("<h1>Welcome to addition</h1>")

def about(request): #view named about
    return render(request,'index.html')

def add(request): #view named contact
    val1=int(request.GET["num1"])
    val2=int(request.GET["num2"])
    res=val1+val2
    return render(request,'result.html',{'result':res})

