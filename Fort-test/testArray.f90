real function main()
  ! implicit none
  
  ! integer, dimension(2) :: array1 = [1, 2]
  ! integer, dimension(2) :: array2 = [4, 5]
  ! integer, dimension(4) :: result
  ! result = array1 // array2

  ! result = SPREAD([array1, array2], dim=2, ncopies=1)
  ! result = RESHAPE([array1, array2], [4])
  
  ! print *, "Original Array:"
  ! print *, original_array
  ! print *, "Reshaped Array:"
  ! print *, reshaped_array

  implicit none

  real, dimension(3, 3) :: original_array
  real, dimension(2, 2) :: sliced_array

  ! 初始化原始数组
  integer i
  original_array = reshape([(i, i=1, 9)], [3, 3])

  ! 打印原始数组
  print *, "Original Array:"
  do i = 1, 3
    print *, original_array(i, :)
  end do

  ! 使用数组切片获取子集
  sliced_array = original_array(1:2, 2:3)

  ! 打印切片后的数组
  print *, "Sliced Array:"
  do i = 1, 2
    print *, sliced_array(i, :)
  end do

  
end function main

