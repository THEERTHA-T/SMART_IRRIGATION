from django.shortcuts import render
from django.http import HttpResponse 

# Create your views here.
def index(request): #view named index
    return HttpResponse("<h1>Welcome to django</h1>")

def about(request): #view named about
    return HttpResponse("<h1>About page</h1>")

def contact(request): #view named contact
    return HttpResponse("<h1>Contact Us</h1>")

