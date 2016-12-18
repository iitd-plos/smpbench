.data				# data section
.text				# code section

.global _start
_start:
 jmp .i6048718
 .i6048704:  movzbl %dl,%eax
 .i6048707:  movzbl %cl,%edx
 .i604870a:  sub    %edx,%eax
 .i604870c:  inc    %ebx
 .i604870e:  add    %eax,%esi
 .i6048710:  cmp    %ebx,%edi
 .i6048712:  nop
 .i6048713:  jmp    .i6048756
 .i6048718:  movzbl 0x80b1260(%ebx),%ecx
 .i604871f:  movzbl 0x88b1260(%ebx),%edx
 .i6048726:  cmp    %dl,%cl
 .i6048728:  jb     .i6048704
 .i604872e:  movzbl %cl,%eax
 .i6048731:  movzbl %dl,%edx
 .i6048734:  sub    %edx,%eax
 .i6048736:  inc    %ebx
 .i6048738:  add    %eax,%esi
 .i604873a:  cmp    %ebx,%edi
 .i604873c:  nop
 .i604873d:  jmp    .i6048756
 .i6048742:  movzbl %dl,%eax
 .i6048745:  movzbl %cl,%edx
 .i6048748:  sub    %edx,%eax
 .i604874a:  inc    %ebx
 .i604874c:  add    %eax,%esi
 .i604874e:  cmp    %ebx,%edi
 .i6048750:  nop
 .i6048751:  jmp    .i6048794
 .i6048756:  movzbl 0x80b1260(%ebx),%ecx
 .i604875d:  movzbl 0x88b1260(%ebx),%edx
 .i6048764:  cmp    %dl,%cl
 .i6048766:  jb     .i6048742
 .i604876c:  movzbl %cl,%eax
 .i604876f:  movzbl %dl,%edx
 .i6048772:  sub    %edx,%eax
 .i6048774:  inc    %ebx
 .i6048776:  add    %eax,%esi
 .i6048778:  cmp    %ebx,%edi
 .i604877a:  nop
 .i604877b:  jmp    .i6048794
 .i6048780:  movzbl %dl,%eax
 .i6048783:  movzbl %cl,%edx
 .i6048786:  sub    %edx,%eax
 .i6048788:  inc    %ebx
 .i604878a:  add    %eax,%esi
 .i604878c:  cmp    %ebx,%edi
 .i604878e:  nop
 .i604878f:  jmp    .i60487d2
 .i6048794:  movzbl 0x80b1260(%ebx),%ecx
 .i604879b:  movzbl 0x88b1260(%ebx),%edx
 .i60487a2:  cmp    %dl,%cl
 .i60487a4:  jb     .i6048780
 .i60487aa:  movzbl %cl,%eax
 .i60487ad:  movzbl %dl,%edx
 .i60487b0:  sub    %edx,%eax
 .i60487b2:  inc    %ebx
 .i60487b4:  add    %eax,%esi
 .i60487b6:  cmp    %ebx,%edi
 .i60487b8:  nop
 .i60487b9:  jmp    .i60487d2
 .i60487be:  movzbl %dl,%eax
 .i60487c1:  movzbl %cl,%edx
 .i60487c4:  sub    %edx,%eax
 .i60487c6:  inc    %ebx
 .i60487c8:  add    %eax,%esi
 .i60487ca:  cmp    %ebx,%edi
 .i60487cc:  nop
 .i60487cd:  jmp    .i6048810
 .i60487d2:  movzbl 0x80b1260(%ebx),%ecx
 .i60487d9:  movzbl 0x88b1260(%ebx),%edx
 .i60487e0:  cmp    %dl,%cl
 .i60487e2:  jb     .i60487be
 .i60487e8:  movzbl %cl,%eax
 .i60487eb:  movzbl %dl,%edx
 .i60487ee:  sub    %edx,%eax
 .i60487f0:  inc    %ebx
 .i60487f2:  add    %eax,%esi
 .i60487f4:  cmp    %ebx,%edi
 .i60487f6:  nop
 .i60487f7:  jmp    .i6048810
 .i60487fc:  movzbl %dl,%eax
 .i60487ff:  movzbl %cl,%edx
 .i6048802:  sub    %edx,%eax
 .i6048804:  inc    %ebx
 .i6048806:  add    %eax,%esi
 .i6048808:  cmp    %ebx,%edi
 .i604880a:  nop
 .i604880b:  jmp    .i604884e
 .i6048810:  movzbl 0x80b1260(%ebx),%ecx
 .i6048817:  movzbl 0x88b1260(%ebx),%edx
 .i604881e:  cmp    %dl,%cl
 .i6048820:  jb     .i60487fc
 .i6048826:  movzbl %cl,%eax
 .i6048829:  movzbl %dl,%edx
 .i604882c:  sub    %edx,%eax
 .i604882e:  inc    %ebx
 .i6048830:  add    %eax,%esi
 .i6048832:  cmp    %ebx,%edi
 .i6048834:  nop
 .i6048835:  jmp    .i604884e
 .i604883a:  movzbl %dl,%eax
 .i604883d:  movzbl %cl,%edx
 .i6048840:  sub    %edx,%eax
 .i6048842:  inc    %ebx
 .i6048844:  add    %eax,%esi
 .i6048846:  cmp    %ebx,%edi
 .i6048848:  nop
 .i6048849:  jmp    .i604888c
 .i604884e:  movzbl 0x80b1260(%ebx),%ecx
 .i6048855:  movzbl 0x88b1260(%ebx),%edx
 .i604885c:  cmp    %dl,%cl
 .i604885e:  jb     .i604883a
 .i6048864:  movzbl %cl,%eax
 .i6048867:  movzbl %dl,%edx
 .i604886a:  sub    %edx,%eax
 .i604886c:  inc    %ebx
 .i604886e:  add    %eax,%esi
 .i6048870:  cmp    %ebx,%edi
 .i6048872:  nop
 .i6048873:  jmp    .i604888c
 .i6048878:  movzbl %dl,%eax
 .i604887b:  movzbl %cl,%edx
 .i604887e:  sub    %edx,%eax
 .i6048880:  inc    %ebx
 .i6048882:  add    %eax,%esi
 .i6048884:  cmp    %ebx,%edi
 .i6048886:  nop
 .i6048887:  jmp    .i60488ca
 .i604888c:  movzbl 0x80b1260(%ebx),%ecx
 .i6048893:  movzbl 0x88b1260(%ebx),%edx
 .i604889a:  cmp    %dl,%cl
 .i604889c:  jb     .i6048878
 .i60488a2:  movzbl %cl,%eax
 .i60488a5:  movzbl %dl,%edx
 .i60488a8:  sub    %edx,%eax
 .i60488aa:  inc    %ebx
 .i60488ac:  add    %eax,%esi
 .i60488ae:  cmp    %ebx,%edi
 .i60488b0:  nop
 .i60488b1:  jmp    .i60488ca
 .i60488b6:  movzbl %dl,%eax
 .i60488b9:  movzbl %cl,%edx
 .i60488bc:  sub    %edx,%eax
 .i60488be:  inc    %ebx
 .i60488c0:  add    %eax,%esi
 .i60488c2:  cmp    %ebx,%edi
 .i60488c4:  nop
 .i60488c5:  jmp    .i6048908
 .i60488ca:  movzbl 0x80b1260(%ebx),%ecx
 .i60488d1:  movzbl 0x88b1260(%ebx),%edx
 .i60488d8:  cmp    %dl,%cl
 .i60488da:  jb     .i60488b6
 .i60488e0:  movzbl %cl,%eax
 .i60488e3:  movzbl %dl,%edx
 .i60488e6:  sub    %edx,%eax
 .i60488e8:  inc    %ebx
 .i60488ea:  add    %eax,%esi
 .i60488ec:  cmp    %ebx,%edi
 .i60488ee:  nop
 .i60488ef:  jmp    .i6048908
 .i60488f4:  nop
 .i60488f5:  nop
 .i60488f6:  nop
 .i60488f7:  nop
 .i60488f8:  nop
 .i60488f9:  nop
 .i60488fa:  nop
 .i60488fb:  nop
 .i60488fc:  nop
 .i60488fd:  nop
 .i60488fe:  nop
 .i60488ff:  nop
 .i6048900:  nop
 .i6048901:  nop
 .i6048902:  nop
 .i6048903:  nop
 .i6048904:  nop
 .i6048905:  nop
 .i6048906:  nop
 .i6048907:  nop
 .i6048908:  lea    0x8(%ebx),%ebx
 .i604890e:  cmp    %ebx,%edi

