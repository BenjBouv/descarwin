# ifndef __EOSERIAL_UTILS_H__
# define __EOSERIAL_UTILS_H__

# include "Array.h"
# include "Object.h"
# include "String.h"

namespace eoserial
{
    /*****************************
     * DESERIALIZATION FUNCTIONS *
     *****************************
    These functions are useful for casting eoserial::objects into simple, primitive
    variables or into class instance which implement eoserial::Persistent.

    The model is always quite the same : 
    - the first argument is the containing object (which is a eoserial::Entity, 
    an object or an array)
    - the second argument is the key or index,
    - the last argument is the value in which we're writing.
    */

    template< class T >
    void unpack( const Object & obj, const std::string & key, T & value )
    {
        static_cast<String*>( obj.find( key )->second )->deserialize( value );
    }

    void unpackObject( const Object & obj, const std::string & key, Persistent & value )
    {
        static_cast<Object*>( obj.find( key )->second )->deserialize( value );
    }

    template< class Container, template<class> class UnpackAlgorithm >
    void unpackArray( const Object & obj, const std::string & key, Container & array )
    {
        static_cast<Array*>( obj.find( key )->second )->deserialize< Container, UnpackAlgorithm >( array );
    }

    template< class T >
    void unpack( const Array & array, unsigned int index, T & value )
    {
        static_cast<String*>( array[ index ] )->deserialize( value );
    }

    void unpackObject( const Array & array, unsigned int index, Persistent & value )
    {
        static_cast<Object*>( array[ index ] )->deserialize( value );
    }

    template< class Container, template<class> class UnpackAlgorithm >
    void unpackArray( const Array & array, unsigned int index, Container & container )
    {
        static_cast<Array*>( array[ index ] )->deserialize< Container, UnpackAlgorithm >( container );
    }

    /*******************************
     *** SERIALIZATION FUNCTIONS ***
     *******************************
     These functions are useful for casting classic objects and 
     eoserial::Persistent objects into eoserial entities which 
     can be manipulated by the framework.
    */

    /**
     * @brief Casts a value of a stream-serializable type (i.e, which implements
     * operator <<) into a JsonString.
     *
     * This is used when serializing the objects : all primitives types should be
     * converted into strings to get more easily manipulated.
     *
     * @param value The value we're converting.
     * @return JsonString wrapper for the value.
     */
    template <typename T>
    String* make( const T & value )
    {
        std::stringstream ss;
        ss << value;
        return new String( ss.str() );
    }

    /**
     * @brief Specialization for strings : no need to convert as they're still
     * usable as strings.
     */
    template<>
    inline String* make( const std::string & value )
    {
        return new String( value );
    }

    /*
     * These functions are useful for automatically serializing STL containers into
     * eoserial arrays which could be used by the framework.
     **/

    /**
     * @brief Functor which explains how to push the value into the eoserial::Array.
     */
    template< class T >
    struct PushAlgorithm
    {
        /**
         * @brief Main operator.
         *
         * @param array The eoserial::array in which we're writing.
         * @param value The variable we are writing.
         */
        virtual void operator()( Array & array, T & value ) = 0;
    };

    /**
     * @brief Push algorithm for primitive variables.
     *
     * This one should be used when inserting primitive (and types which implement
     * operator<<) variables.
     */
    template< class T >
    struct MakeAlgorithm : PushAlgorithm<T>
    {
        void operator()( Array & array, T & value )
        {
            array.push_back( make( value ) );
        }
    };

    /**
     * @brief Push algorithm for eoserial::Persistent variables.
     */
    struct SerializablePushAlgorithm : PushAlgorithm< Persistent >
    {
        void operator()( Array & array, Persistent & obj )
        {
            // obj address is not saved into array.push_back.
            array.push_back( &obj );
        }
    };

    /**
     * @brief Casts a STL container (vector<int> or list<std::string>, for instance)
     * into a eoserial::Array.
     *
     * @þaram PushAlgorithm The algorithm used for inserting new element in the eoserial::Array.
     * This algorithm is directly called, so it is its own charge to invoke push_back on the 
     * eoserial::Array.
     */
    template< class Container, template<class> class PushAlgorithm >
    Array* makeArray( Container & array )
    {
        Array* returned_array = new Array;
        typedef typename Container::iterator iterator;
        typedef typename Container::value_type type;
        PushAlgorithm< type > algo;
        for (
                iterator it = array.begin(), end = array.end();
                it != end;
                ++it)
        {
            algo( *returned_array, *it );
        }
        return returned_array;
    }
} // namespace eoserial

# endif //__EOSERIAL_UTILS_H__
