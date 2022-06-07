from django.shortcuts import render
from django.http import HttpResponse
from . models import Product
# Create your views here.

def dbproduct(request):
    products=Product.objects.all()
    return render(request,'dbproduct.html',{'products':products})
