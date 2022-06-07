#urls from main project. To access from main project

from django.contrib import admin
from django.urls import path, include

urlpatterns = [
    path('',include('db.urls')),
   # path('', include('calc.urls')),
        #path('test2/', include('test2.urls')),

    path('admin/', admin.site.urls),

]
