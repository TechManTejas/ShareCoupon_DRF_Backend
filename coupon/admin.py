from django.contrib import admin
from .models import Coupon

@admin.register(Coupon)
class CouponAdmin(admin.ModelAdmin):
    list_display = ('title', 'user', 'category', 'likes')
    search_fields = ('title', 'user__username', 'category')
