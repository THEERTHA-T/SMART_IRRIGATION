#urls from same app

from . import views
# . means same folder

from django.urls import path

urlpatterns = [
    path('', views.dbproduct,name='dbproduct'),
    #path('about', views.about,name='about'),
    #path('contact', views.contact,name='contact')
]
