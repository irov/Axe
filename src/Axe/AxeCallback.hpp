//////////////////////////////////////////////////////////////////////////
namespace Axe
{
	namespace Helper
	{
		//////////////////////////////////////////////////////////////////////////
		struct FunctorArguments0
			: public AxeUtil::Shared
		{
			static const int arity = 0;
		};
		//////////////////////////////////////////////////////////////////////////
		template< class A0 >
		struct FunctorArguments1
			: public AxeUtil::Shared
		{
			static const int arity = 1;
			A0 a0;
		};
		//////////////////////////////////////////////////////////////////////////
		template< class A0, class A1 >
		struct FunctorArguments2
			: public AxeUtil::Shared
		{
			static const int arity = 2;
			A0 a0;
			A1 a1;
		};
		//////////////////////////////////////////////////////////////////////////
		template< class A0, class A1, class A2 >
		struct FunctorArguments3
			: public AxeUtil::Shared
		{
			static const int arity = 3;
			A0 a0;
			A1 a1;
			A2 a2;
		};
		//////////////////////////////////////////////////////////////////////////
		template<class F, class Arguments>
		class FunctionCallbackBase
		{
		public:
			FunctionCallbackBase( F _func, const boost::intrusive_ptr<Arguments> & _args )
			: m_func(_func)
			, m_arguments(_args)
			{}
		public:
			const boost::intrusive_ptr<Arguments> & arguments() const
			{
				return m_arguments;
			}
		protected:
			F m_func;
			boost::intrusive_ptr<Arguments> m_arguments;
		};
		//////////////////////////////////////////////////////////////////////////
		template<class F, class Arguments, class P>
		class FunctionCallback;
		//////////////////////////////////////////////////////////////////////////
		template<class F, class Arguments>
		class FunctionCallback<F, Arguments, void (*)()>
			: public FunctionCallbackBase<F,Arguments>
		{
		public:
			FunctionCallback( F _func, const boost::intrusive_ptr<Arguments> & _args )
				: FunctionCallbackBase<F,Arguments>(_func,_args)
			{}
		public:
			void call()
			{
				(*m_func)();
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class F, class Arguments, class A0 >
		class FunctionCallback<F, Arguments, void (*)(A0)>
			: public FunctionCallbackBase<F,Arguments>
		{
		public:
			FunctionCallback( F _func, const boost::intrusive_ptr<Arguments> & _args )
				: FunctionCallbackBase<F,Arguments>(_func,_args)
			{}
		public:
			void call( A0 _a0 )
			{
				(*m_func)(_a0);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class F, class Arguments, class A0, class A1 >
		class FunctionCallback<F, Arguments, void (*)(A0,A1)>
			: public FunctionCallbackBase<F,Arguments>
		{
		public:
			FunctionCallback( F _func, const boost::intrusive_ptr<Arguments> & _args )
				: FunctionCallbackBase<F,Arguments>(_func,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1 )
			{
				(*m_func)(_a0,_a1);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class F, class Arguments, class A0, class A1, class A2 >
		class FunctionCallback<F, Arguments, void (*)(A0,A1,A2)>
			: public FunctionCallbackBase<F,Arguments>
		{
		public:
			FunctionCallback( F _func, const boost::intrusive_ptr<Arguments> & _args )
				: FunctionCallbackBase<F,Arguments>(_func,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2 )
			{
				(*m_func)(_a0,_a1,_a2);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class F, class Arguments, class A0, class A1, class A2, class A3 >
		class FunctionCallback<F, Arguments, void (*)(A0,A1,A2,A3)>
			: public FunctionCallbackBase<F,Arguments>
		{
		public:
			FunctionCallback( F _func, const boost::intrusive_ptr<Arguments> & _args )
				: FunctionCallbackBase<F,Arguments>(_func,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2, A3 _a3 )
			{
				(*m_func)(_a0,_a1,_a2,_a3);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class F, class Arguments, class A0, class A1, class A2, class A3, class A4 >
		class FunctionCallback<F, Arguments, void (*)(A0,A1,A2,A3,A4)>
			: public FunctionCallbackBase<F,Arguments>
		{
		public:
			FunctionCallback( F _func, const boost::intrusive_ptr<Arguments> & _args )
				: FunctionCallbackBase<F,Arguments>(_func,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2, A3 _a3, A4 _a4 )
			{
				(*m_func)(_a0,_a1,_a2,_a3,_a4);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class F, class Arguments, class A0, class A1, class A2, class A3, class A4, class A5 >
		class FunctionCallback<F, Arguments, void (*)(A0,A1,A2,A3,A4,A5)>
			: public FunctionCallbackBase<F,Arguments>
		{
		public:
			FunctionCallback( F _func, const boost::intrusive_ptr<Arguments> & _args )
				: FunctionCallbackBase<F,Arguments>(_func,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2, A3 _a3, A4 _a4, A5 _a5 )
			{
				(*m_func)(_a0,_a1,_a2,_a3,_a4,_a5);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class F, class Arguments, class A0, class A1, class A2, class A3, class A4, class A5, class A6 >
		class FunctionCallback<F, Arguments, void (*)(A0,A1,A2,A3,A4,A5,A6)>
			: public FunctionCallbackBase<F,Arguments>
		{
		public:
			FunctionCallback( F _func, const boost::intrusive_ptr<Arguments> & _args )
				: FunctionCallbackBase<F,Arguments>(_func,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2, A3 _a3, A4 _a4, A5 _a5, A6 _a6 )
			{
				(*m_func)(_a0,_a1,_a2,_a3,_a4,_a5,_a6);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class F, class Arguments>
		FunctionCallback<F,Arguments,F> makeFunctionCallback( F _func, const boost::intrusive_ptr<Arguments> & _args )
		{
			return FunctionCallback<F,Arguments,F>(_func, _args);
		}
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments>
		class MethodCallbackBase
		{
		public:
			MethodCallbackBase( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
			: m_self(_self)
			, m_method(_method)
			, m_arguments(_args)
			{}
		public:
			const boost::intrusive_ptr<Arguments> & arguments() const
			{
				return m_arguments;
			}
		protected:
			boost::intrusive_ptr<C> m_self;
			M m_method;
			boost::intrusive_ptr<Arguments> m_arguments;
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class P>
		class MethodCallback;
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments>
		class MethodCallback<C, M, Arguments, void (C::*)()>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call()
			{
				C * pure_self = &*m_self;
				(pure_self->*m_method)();
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments>
		class MethodCallback<C, M, Arguments, void (C::*)() const>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call()
			{
				const C * pure_self = &*m_self;
				(pure_self->*m_method)();
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0)>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0 )
			{
				C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0) const>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0 )
			{
				const C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0, class A1 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0,A1)>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1 )
			{
				C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0,_a1);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0, class A1 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0,A1) const>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1 )
			{
				const C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0,_a1);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0, class A1, class A2 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0,A1,A2)>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2 )
			{
				C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0,_a1,_a2);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0, class A1, class A2 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0,A1,A2) const>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2 )
			{
				const C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0,_a1,_a2);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0, class A1, class A2, class A3 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0,A1,A2,A3)>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2, A3 _a3 )
			{
				C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0,_a1,_a2,_a3);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0, class A1, class A2, class A3 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0,A1,A2,A3) const>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2, A3 _a3 )
			{
				const C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0,_a1,_a2,_a3);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0, class A1, class A2, class A3, class A4 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0,A1,A2,A3,A4)>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2, A3 _a3, A4 _a4 )
			{
				C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0,_a1,_a2,_a3,_a4);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0, class A1, class A2, class A3, class A4 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0,A1,A2,A3,A4) const>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2, A3 _a3, A4 _a4 )
			{
				const C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0,_a1,_a2,_a3,_a4);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0, class A1, class A2, class A3, class A4, class A5 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0,A1,A2,A3,A4,A5)>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2, A3 _a3, A4 _a4, A5 _a5 )
			{
				C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0,_a1,_a2,_a3,_a4,_a5);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0, class A1, class A2, class A3, class A4, class A5 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0,A1,A2,A3,A4,A5) const>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2, A3 _a3, A4 _a4, A5 _a5 )
			{
				const C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0,_a1,_a2,_a3,_a4,_a5);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0, class A1, class A2, class A3, class A4, class A5, class A6 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0,A1,A2,A3,A4,A5,A6)>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2, A3 _a3, A4 _a4, A5 _a5, A6 _a6 )
			{
				C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0,_a1,_a2,_a3,_a4,_a5,_a6);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments, class A0, class A1, class A2, class A3, class A4, class A5, class A6 >
		class MethodCallback<C, M, Arguments, void (C::*)(A0,A1,A2,A3,A4,A5,A6) const>
			: public MethodCallbackBase<C,M,Arguments>
		{
		public:
			MethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
				: MethodCallbackBase<C,M,Arguments>(_self,_method,_args)
			{}
		public:
			void call( A0 _a0, A1 _a1, A2 _a2, A3 _a3, A4 _a4, A5 _a5, A6 _a6 )
			{
				const C * pure_self = &*m_self;
				(pure_self->*m_method)(_a0,_a1,_a2,_a3,_a4,_a5,_a6);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class C, class M, class Arguments>
		MethodCallback<C,M,Arguments,M> makeMethodCallback( const boost::intrusive_ptr<C> & _self, M _method, const boost::intrusive_ptr<Arguments> & _args )
		{
			return MethodCallback<C,M,Arguments,F>(_self,_method, _args);
		}
		//////////////////////////////////////////////////////////////////////////
		template<class Functor, class Arguments, int Arity>
		class CallFunctor;
		//////////////////////////////////////////////////////////////////////////
		template<class Functor, class Arguments>
		class CallFunctor<Functor,Arguments,0>
		{
		public:
			static void call0( Functor _func, const boost::intrusive_ptr<Arguments> & _args )
			{
				_func.call();
			}
			template< class R0 >
			static void call1( Functor _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0)
			{
				_func.call(_r0);
			}
			template< class R0, class R1 >
			static void call2( Functor _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0, const R1 & _r1)
			{
				_func.call(_r0,_r1);
			}
			template< class R0, class R1, class R2 >
			static void call3( Functor _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0, const R1 & _r1, const R2 & _r2)
			{
				_func.call(_r0,_r1,_r2);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class Functor, class Arguments>
		class CallFunctor<Functor,Arguments,1>
		{
		public:
			static void call0( Functor _func, const boost::intrusive_ptr<Arguments> & _args )
			{
				_func.call(_args->a0);
			}
			template< class R0 >
			static void call1( Functor _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0)
			{
				_func.call(_r0,_args->a0);
			}
			template< class R0, class R1 >
			static void call2( Functor _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0, const R1 & _r1)
			{
				_func.call(_r0,_r1,_args->a0);
			}
			template< class R0, class R1, class R2 >
			static void call3( Functor _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0, const R1 & _r1, const R2 & _r2)
			{
				_func.call(_r0,_r1,_r2,_args->a0);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class Functor, class Arguments>
		class CallFunctor<Functor,Arguments,2>
		{
		public:
			static void call0( Functor _func, const boost::intrusive_ptr<Arguments> & _args )
			{
				_func.call(_args->a0,_args->a1);
			}
			template< class R0 >
			static void call1( Functor _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0)
			{
				_func.call(_r0,_args->a0,_args->a1);
			}
			template< class R0, class R1 >
			static void call2( Functor _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0, const R1 & _r1)
			{
				_func.call(_r0,_r1,_args->a0,_args->a1);
			}
			template< class R0, class R1, class R2 >
			static void call3( Functor _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0, const R1 & _r1, const R2 & _r2)
			{
				_func.call(_r0,_r1,_r2,_args->a0,_args->a1);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class Functor, class Arguments>
		class CallFunctor<Functor,Arguments,3>
		{
		public:
			static void call0( Functor _func, const boost::intrusive_ptr<Arguments> & _args )
			{
				_func.call(_args->a0,_args->a1,_args->a2);
			}
			template< class R0 >
			static void call1( Functor _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0)
			{
				_func.call(_r0,_args->a0,_args->a1,_args->a2);
			}
			template< class R0, class R1 >
			static void call2( Functor _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0, const R1 & _r1)
			{
				_func.call(_r0,_r1,_args->a0,_args->a1,_args->a2);
			}
			template< class R0, class R1, class R2 >
			static void call3( Functor _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0, const R1 & _r1, const R2 & _r2)
			{
				_func.call(_r0,_r1,_r2,_args->a0,_args->a1,_args->a2);
			}
		};
		//////////////////////////////////////////////////////////////////////////
		template<class Functor, class Arguments>
		void callFunctor0( const Functor & _func, const boost::intrusive_ptr<Arguments> & _args)
		{
			CallFunctor<Functor, Arguments, Arguments::arity>::call0( _func, _args);
		}
		//////////////////////////////////////////////////////////////////////////
		template<class Functor, class Arguments, class R0 >
		void callFunctor1( const Functor & _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0)
		{
			CallFunctor<Functor, Arguments, Arguments::arity>::call1( _func, _args,_r0);
		}
		//////////////////////////////////////////////////////////////////////////
		template<class Functor, class Arguments, class R0, class R1 >
		void callFunctor2( const Functor & _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0, const R1 & _r1)
		{
			CallFunctor<Functor, Arguments, Arguments::arity>::call2( _func, _args,_r0,_r1);
		}
		//////////////////////////////////////////////////////////////////////////
		template<class Functor, class Arguments, class R0, class R1, class R2 >
		void callFunctor3( const Functor & _func, const boost::intrusive_ptr<Arguments> & _args, const R0 & _r0, const R1 & _r1, const R2 & _r2)
		{
			CallFunctor<Functor, Arguments, Arguments::arity>::call3( _func, _args,_r0,_r1,_r2);
		}
		//////////////////////////////////////////////////////////////////////////
		template<class AMI, class CR, class CE>
		class AMICallbackAdapter0
			: public AMI
		{
		public:
			AMICallbackAdapter0( const CR & _response, const CE & _exception )
				: m_response(_response)
				, m_exception(_exception)
			{}
		
		protected:
			void response()
			{
				callFunctor0( m_response, m_response.arguments());
			}
		
			void throw_exception( const Axe::Exception & _ex )
			{
				callFunctor1( m_exception, m_exception.arguments(), _ex );
			}
		
		protected:
			CR m_response;
			CE m_exception;
		};
		//////////////////////////////////////////////////////////////////////////
		template<class AMI, class CR, class CE, class P0 >
		class AMICallbackAdapter1
			: public AMI
		{
		public:
			AMICallbackAdapter1( const CR & _response, const CE & _exception )
				: m_response(_response)
				, m_exception(_exception)
			{}
		
		protected:
			void response( P0 _p0 )
			{
				callFunctor1( m_response, m_response.arguments(),_p0);
			}
		
			void throw_exception( const Axe::Exception & _ex )
			{
				callFunctor1( m_exception, m_exception.arguments(), _ex );
			}
		
		protected:
			CR m_response;
			CE m_exception;
		};
		//////////////////////////////////////////////////////////////////////////
		template<class AMI, class CR, class CE, class P0, class P1 >
		class AMICallbackAdapter2
			: public AMI
		{
		public:
			AMICallbackAdapter2( const CR & _response, const CE & _exception )
				: m_response(_response)
				, m_exception(_exception)
			{}
		
		protected:
			void response( P0 _p0, P1 _p1 )
			{
				callFunctor2( m_response, m_response.arguments(),_p0,_p1);
			}
		
			void throw_exception( const Axe::Exception & _ex )
			{
				callFunctor1( m_exception, m_exception.arguments(), _ex );
			}
		
		protected:
			CR m_response;
			CE m_exception;
		};
		//////////////////////////////////////////////////////////////////////////
		template<class AMI, class CR, class CE, class P0, class P1, class P2 >
		class AMICallbackAdapter3
			: public AMI
		{
		public:
			AMICallbackAdapter3( const CR & _response, const CE & _exception )
				: m_response(_response)
				, m_exception(_exception)
			{}
		
		protected:
			void response( P0 _p0, P1 _p1, P2 _p2 )
			{
				callFunctor3( m_response, m_response.arguments(),_p0,_p1,_p2);
			}
		
			void throw_exception( const Axe::Exception & _ex )
			{
				callFunctor1( m_exception, m_exception.arguments(), _ex );
			}
		
		protected:
			CR m_response;
			CE m_exception;
		};
		//////////////////////////////////////////////////////////////////////////
		template<class AMI, class CR, class CE, class M>
		AMI * makeAmiCallbackAdapter( const CR & _response, const CE & _exception, M _method );
		//////////////////////////////////////////////////////////////////////////
		template<class AMI, class CR, class CE, class C>
		AMI * makeAmiCallbackAdapter( const CR & _response, const CE & _exception, void (C::*)() )
		{
			return new AMICallbackAdapter0<AMI, CR, CE>(_response, _exception);
		}
		//////////////////////////////////////////////////////////////////////////
		template<class AMI, class CR, class CE, class C, class P0 >
		AMI * makeAmiCallbackAdapter( const CR & _response, const CE & _exception, void (C::*)(P0) )
		{
			return new AMICallbackAdapter1<AMI, CR, CE,P0>(_response, _exception);
		}
		//////////////////////////////////////////////////////////////////////////
		template<class AMI, class CR, class CE, class C, class P0, class P1 >
		AMI * makeAmiCallbackAdapter( const CR & _response, const CE & _exception, void (C::*)(P0,P1) )
		{
			return new AMICallbackAdapter2<AMI, CR, CE,P0,P1>(_response, _exception);
		}
		//////////////////////////////////////////////////////////////////////////
		template<class AMI, class CR, class CE, class C, class P0, class P1, class P2 >
		AMI * makeAmiCallbackAdapter( const CR & _response, const CE & _exception, void (C::*)(P0,P1,P2) )
		{
			return new AMICallbackAdapter3<AMI, CR, CE,P0,P1,P2>(_response, _exception);
		}
		//////////////////////////////////////////////////////////////////////////
		template<class CR, class CE>
		class AMICallbackGenerator
		{
		public:
			AMICallbackGenerator(const CR & _response, const CE & _exception)
				: m_response(_response)
				, m_exception(_exception)
		{}
		public:
			template<class AMI>
			operator boost::intrusive_ptr<AMI> ()
			{
				return makeAmiCallbackAdapter<AMI>( m_response, m_exception, &AMI::response );
			}
		
		protected:
			CR m_response;
			CE m_exception;
		};
	}
	//////////////////////////////////////////////////////////////////////////
	template<class CR, class CE>
	Helper::AMICallbackGenerator<CR,CE> amiCallback( CR _response, CE _exception )
	{
		return Helper::AMICallbackGenerator<CR,CE>(_response, _exception);
	}
	//////////////////////////////////////////////////////////////////////////
	template<class F>
	Helper::FunctionCallback<F, Helper::FunctorArguments0, F> amiFunction( F _func)
	{
		return Helper::FunctionCallback<F, Helper::FunctorArguments0, F>( _func, 0 );
	}
	//////////////////////////////////////////////////////////////////////////
	template<class F, class A0 >
	Helper::FunctionCallback<F, Helper::FunctorArguments1<A0>, F> amiFunction( F _func, const A0 & _a0)
	{
		Helper::FunctorArguments1<A0> * args = new Helper::FunctorArguments1<A0>();
		args->a0 = _a0;
		return Helper::FunctionCallback<F, Helper::FunctorArguments1<A0>, F>( _func, args );
	}
	//////////////////////////////////////////////////////////////////////////
	template<class F, class A0, class A1 >
	Helper::FunctionCallback<F, Helper::FunctorArguments2<A0,A1>, F> amiFunction( F _func, const A0 & _a0, const A1 & _a1)
	{
		Helper::FunctorArguments2<A0,A1> * args = new Helper::FunctorArguments2<A0,A1>();
		args->a0 = _a0;
		args->a1 = _a1;
		return Helper::FunctionCallback<F, Helper::FunctorArguments2<A0,A1>, F>( _func, args );
	}
	//////////////////////////////////////////////////////////////////////////
	template<class F, class A0, class A1, class A2 >
	Helper::FunctionCallback<F, Helper::FunctorArguments3<A0,A1,A2>, F> amiFunction( F _func, const A0 & _a0, const A1 & _a1, const A2 & _a2)
	{
		Helper::FunctorArguments3<A0,A1,A2> * args = new Helper::FunctorArguments3<A0,A1,A2>();
		args->a0 = _a0;
		args->a1 = _a1;
		args->a2 = _a2;
		return Helper::FunctionCallback<F, Helper::FunctorArguments3<A0,A1,A2>, F>( _func, args );
	}
	//////////////////////////////////////////////////////////////////////////
	template<class C, class M>
	Helper::MethodCallback<C,M, Helper::FunctorArguments0, M> amiMethod( const boost::intrusive_ptr<C> & _self, M _method)
	{
		return Helper::MethodCallback<C,M,Helper::FunctorArguments0, M>( _self, _method, 0 );
	}
	//////////////////////////////////////////////////////////////////////////
	template<class C, class M>
	Helper::MethodCallback<C,M, Helper::FunctorArguments0, M> amiMethod( C * _self, M _method)
	{
		boost::intrusive_ptr<C> smart_self(_self);
		return amiMethod( smart_self, _method);
	}
	//////////////////////////////////////////////////////////////////////////
	template<class C, class M, class A0 >
	Helper::MethodCallback<C,M, Helper::FunctorArguments1<A0>, M> amiMethod( const boost::intrusive_ptr<C> & _self, M _method, const A0 & _a0)
	{
		Helper::FunctorArguments1<A0> * args = new Helper::FunctorArguments1<A0>();
		args->a0 = _a0;
		return Helper::MethodCallback<C,M,Helper::FunctorArguments1<A0>, M>( _self, _method, args );
	}
	//////////////////////////////////////////////////////////////////////////
	template<class C, class M, class A0 >
	Helper::MethodCallback<C,M, Helper::FunctorArguments1<A0>, M> amiMethod( C * _self, M _method, const A0 & _a0)
	{
		boost::intrusive_ptr<C> smart_self(_self);
		return amiMethod( smart_self, _method,_a0);
	}
	//////////////////////////////////////////////////////////////////////////
	template<class C, class M, class A0, class A1 >
	Helper::MethodCallback<C,M, Helper::FunctorArguments2<A0,A1>, M> amiMethod( const boost::intrusive_ptr<C> & _self, M _method, const A0 & _a0, const A1 & _a1)
	{
		Helper::FunctorArguments2<A0,A1> * args = new Helper::FunctorArguments2<A0,A1>();
		args->a0 = _a0;
		args->a1 = _a1;
		return Helper::MethodCallback<C,M,Helper::FunctorArguments2<A0,A1>, M>( _self, _method, args );
	}
	//////////////////////////////////////////////////////////////////////////
	template<class C, class M, class A0, class A1 >
	Helper::MethodCallback<C,M, Helper::FunctorArguments2<A0,A1>, M> amiMethod( C * _self, M _method, const A0 & _a0, const A1 & _a1)
	{
		boost::intrusive_ptr<C> smart_self(_self);
		return amiMethod( smart_self, _method,_a0,_a1);
	}
	//////////////////////////////////////////////////////////////////////////
	template<class C, class M, class A0, class A1, class A2 >
	Helper::MethodCallback<C,M, Helper::FunctorArguments3<A0,A1,A2>, M> amiMethod( const boost::intrusive_ptr<C> & _self, M _method, const A0 & _a0, const A1 & _a1, const A2 & _a2)
	{
		Helper::FunctorArguments3<A0,A1,A2> * args = new Helper::FunctorArguments3<A0,A1,A2>();
		args->a0 = _a0;
		args->a1 = _a1;
		args->a2 = _a2;
		return Helper::MethodCallback<C,M,Helper::FunctorArguments3<A0,A1,A2>, M>( _self, _method, args );
	}
	//////////////////////////////////////////////////////////////////////////
	template<class C, class M, class A0, class A1, class A2 >
	Helper::MethodCallback<C,M, Helper::FunctorArguments3<A0,A1,A2>, M> amiMethod( C * _self, M _method, const A0 & _a0, const A1 & _a1, const A2 & _a2)
	{
		boost::intrusive_ptr<C> smart_self(_self);
		return amiMethod( smart_self, _method,_a0,_a1,_a2);
	}
}
