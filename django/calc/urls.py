#urls from same app

from . import views
# . means same folder

from django.urls import path

urlpatterns = [
   # path('', views.index,name='index'),
    path('', views.about,name='about'),
    path('add', views.add,name='add')
]
