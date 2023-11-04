from django.db import models
from django.contrib.auth.models import User

class Coupon(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    image = models.ImageField(upload_to='coupons/', null=True, blank=True)
    title = models.CharField(max_length=100)
    description = models.TextField(blank=True)
    status = models.CharField(max_length=20, blank=True, default="Active")
    category = models.CharField(max_length=50, blank=True, null=True, default=None)
    likes = models.IntegerField(default=0, blank=True, null=True)
    chats = models.JSONField(blank=True, null=True)

    def __str__(self):
        return self.title