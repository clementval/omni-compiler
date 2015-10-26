! testp052.f
! reduction指示文(-)のテスト

      program main
      include 'xmp_lib.h'
      integer,parameter:: N=1000
!$xmp nodes p(4,*)
!$xmp template t(N,N)
!$xmp distribute t(block,block) onto p
      integer a(N,N), sa
      real*8  b(N,N), sb
      real*4  c(N,N), sc
      character(len=2) result
!$xmp align a(i,j) with t(i,j)
!$xmp align b(i,j) with t(i,j)
!$xmp align c(i,j) with t(i,j)

      if(xmp_num_nodes().lt.16) then
         print *, 'You have to run this program by more than 16 nodes.'
      endif

      sa = 0
      sb = 0.0
      sc = 0.0

!$xmp loop (i,j) on t(i,j)
      do j=1, N
         do i=1, N
            a(i,j) = 1
            b(i,j) = 0.5
            c(i,j) = 0.25
         enddo
      enddo

!$xmp loop (i,j) on t(i,j)
      do j=1, N
         do i=1, N
            sa = sa-a(i,j)
         enddo
      enddo
!$xmp reduction(-:sa)

!$xmp loop (i,j) on t(i,j)
      do j=1, N
         do i=1, N
            sb = sb-b(i,j)
         enddo
      enddo
!$xmp reduciton(-:sb)

!$xmp loop (i,j) on t(i,j)
      do j=1, N
         do i=1, N
            sc = sc-c(i,j)
         enddo
      enddo
!$xmp reduciton(-:sc)
      
      result = 'OK'
      if(  sa .ne. -((N**2)) .or.
     $     abs(sb+(dble(N**2)*0.5)) .gt. 0.000001 .or.
     $     abs(sc+(real(N**2)*0.25)) .gt. 0.0001) then
         result = 'NG'
      endif

      print *, xmp_node_num(), 'testp052.f ', result

      end
