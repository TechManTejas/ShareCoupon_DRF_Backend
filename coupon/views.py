from rest_framework import viewsets
from .models import Coupon
from .serializers import CouponSerializer

class CouponPublicViewSet(viewsets.ModelViewSet):
    queryset = Coupon.objects.all()
    serializer_class = CouponSerializer

class CouponPrivateViewSet(viewsets.ModelViewSet):
    queryset = Coupon.objects.all()
    serializer_class = CouponSerializer

    def get_queryset(self):
        return Coupon.objects.filter(user=self.request.user)