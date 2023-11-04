from rest_framework import viewsets, status
from rest_framework.response import Response
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
    
    def create(self, serializer):
        # Get the user associated with the provided access token
        user = self.request.user
        print(user)

        image = self.request.data.get('image')
        title = self.request.data.get('title')
        description = self.request.data.get('description')
        category = self.request.data.get('category')

        # Create the Coupon object with the provided data
        coupon = Coupon(
            user=user,
            image=image,
            title=title,
            description=description,
            category=category
        )

        coupon.save()
        return Response(serializer.data, status=status.HTTP_201_CREATED)