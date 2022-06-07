#urls from same app

from . import views
# . means same folder

from django.urls import path

urlpatterns = [
    path('', views.index,name='index'),
    path('about', views.about,name='about'),
    path('contact', views.contact,name='contact')
]
