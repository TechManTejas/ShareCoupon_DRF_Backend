from rest_framework import serializers
from user.serializers import UserSerializer
from .models import Coupon

class CouponSerializer(serializers.ModelSerializer):
    user = UserSerializer()
    class Meta:
        model = Coupon
        fields = '__all__'
